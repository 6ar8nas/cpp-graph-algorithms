#include "Graph.h"
#include "MinHeap.h"
#include "FibonacciHeap.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_set>

std::random_device dev;
std::mt19937 rng(dev());

Graph::Graph(int V) : V(V)
{
    if (V < 0)
        throw std::invalid_argument("The number of vertices must be non-negative.");

    adj = new std::unordered_set<Edge, Edge::AdjListHash, Edge::DirectedEqual>[V];
}

Graph::Graph(int V, int KMinIn, int KMaxIn, int KMinOut, int KMaxOut) : Graph(V)
{
    if (KMinIn < 0 || KMaxIn < KMinIn || KMinOut < 0 || KMaxOut < KMinOut)
        throw std::invalid_argument("Invalid edge constraints, all values must be non-negative and KMax >= KMin.");

    std::uniform_int_distribution<int> edgesIn(KMinIn, KMaxIn);
    std::uniform_int_distribution<int> edgesOut(KMinOut, KMaxOut);
    std::uniform_int_distribution<int> weight(1, 15);
    std::uniform_int_distribution<int> randomVertex(0, V - 1);

    std::vector<int> inDegrees(V, 0);
    std::vector<int> outDegrees(V, 0);

    for (int i = 0; i < V; ++i)
    {
        int ingoingEdges = edgesIn(rng);
        int outgoingEdges = edgesOut(rng);

        for (int iter = 0; inDegrees[i] < ingoingEdges && iter < 3 * V; ++iter)
        {
            int targetVertex = randomVertex(rng);
            if (targetVertex != i && outDegrees[targetVertex] < KMaxOut && !hasEdge({targetVertex, i}))
            {
                addEdge({targetVertex, i, weight(rng)});
                inDegrees[i]++;
                outDegrees[targetVertex]++;
            }
        }

        for (int iter = 0; outDegrees[i] < outgoingEdges && iter < 3 * V; ++iter)
        {
            int targetVertex = randomVertex(rng);
            if (targetVertex != i && inDegrees[targetVertex] < KMaxIn && !hasEdge({i, targetVertex}))
            {
                addEdge({i, targetVertex, weight(rng)});
                outDegrees[i]++;
                inDegrees[targetVertex]++;
            }
        }

        if (outDegrees[i] < KMinOut || inDegrees[i] < KMinIn)
            throw std::runtime_error("Could not generate a graph with the specified number of edges.");
    }
}

Graph::Graph(int V, const std::vector<Edge> &edges) : Graph(V)
{
    for (const auto &edge : edges)
        addEdge(edge);
}

Graph::~Graph()
{
    delete[] adj;
}

bool Graph::addEdge(const Edge &edge)
{
    if (V <= edge.src || V <= edge.dest)
        throw std::invalid_argument("The vertices must be within the range of the graph.");

    return (adj[edge.src].insert(edge)).second;
}

bool Graph::removeEdge(const Edge &edge)
{
    if (V <= edge.src || V <= edge.dest)
        throw std::invalid_argument("The vertices must be within the range of the graph.");

    return adj[edge.src].erase(edge);
}

bool Graph::hasEdge(const Edge &edge) const
{
    return adj[edge.src].count(edge) != 0;
}

std::pair<std::unordered_map<int, VertexInfo>, double> Graph::dijkstraMinHeap(int source) const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    auto maxValue = std::numeric_limits<int>::max() / 2;
    std::unordered_map<int, VertexInfo> verticesData;
    for (int i = 0; i < V; ++i)
        verticesData.emplace(i, VertexInfo(i, maxValue, -1));
    verticesData.at(source).distance = 0;

    MinHeap<VertexInfo, VertexInfo::DijkstraHash, VertexInfo::DijkstraEqual> minHeap;
    for (const auto &entry : verticesData)
        minHeap.insert(entry.second);

    while (!minHeap.isEmpty())
    {
        auto u = minHeap.extractMin();
        verticesData.at(u.vertex).isRemoved = true;
        for (const Edge &edge : adj[u.vertex])
        {
            if (verticesData.at(edge.dest).isRemoved)
                continue;

            int newDist = verticesData.at(u.vertex).distance + edge.weight;
            if (newDist < verticesData.at(edge.dest).distance)
            {
                verticesData.at(edge.dest).distance = newDist;
                verticesData.at(edge.dest).parent = u.vertex;
                minHeap.decreaseKey(verticesData.at(edge.dest), verticesData.at(edge.dest));
            }
        }
    }

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    return std::make_pair(verticesData, duration.count());
}

std::pair<std::unordered_map<int, VertexInfo>, double> Graph::dijkstraFibHeap(int source) const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    auto maxValue = std::numeric_limits<int>::max() / 2;
    std::unordered_map<int, VertexInfo> verticesData;
    for (int i = 0; i < V; ++i)
        verticesData.emplace(i, VertexInfo(i, maxValue, -1));
    verticesData.at(source).distance = 0;

    std::unordered_map<int, FibonacciHeapNode<VertexInfo> *> nodeReferences;
    FibonacciHeap<VertexInfo> fibHeap;
    for (const auto &entry : verticesData)
        nodeReferences.emplace(entry.first, fibHeap.insert(entry.second));

    while (!fibHeap.isEmpty())
    {
        auto u = fibHeap.extractMin();
        verticesData.at(u.vertex).isRemoved = true;
        for (const Edge &edge : adj[u.vertex])
        {
            if (verticesData.at(edge.dest).isRemoved)
                continue;

            int newDist = verticesData.at(u.vertex).distance + edge.weight;
            if (newDist < verticesData.at(edge.dest).distance)
            {
                verticesData.at(edge.dest).distance = newDist;
                verticesData.at(edge.dest).parent = u.vertex;
                fibHeap.decreaseKey(nodeReferences.at(edge.dest), verticesData.at(edge.dest));
            }
        }
    }

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    return std::make_pair(verticesData, duration.count());
}

void Graph::printDijkstraResults(int source, const std::unordered_map<int, VertexInfo> &distances, double duration)
{
    for (const auto &entry : distances)
    {
        std::vector<int> path;
        int current = entry.second.vertex;
        while (current != -1)
        {
            path.push_back(current);
            current = distances.at(current).parent;
        }
        std::cout << "Vertex: " << entry.second.vertex << ", distance: " << entry.second.distance << ", path: ";
        if (path.back() != source)
        {
            std::cout << "No path exists" << std::endl;
            continue;
        }

        for (int i = path.size() - 1; i >= 0; --i)
        {
            std::cout << path[i];
            if (i > 0)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    std::cout << "Dijkstra took " << duration << " seconds." << std::endl;
}