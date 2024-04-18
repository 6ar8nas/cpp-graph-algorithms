#include "utils.h"
#include "Graph.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <queue>

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
    std::uniform_int_distribution<int> weight(0, 10);
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

void Graph::printGraph() const
{
    for (int i = 0; i < V; ++i)
    {
        std::cout << i << " -> ";
        for (const auto &vertex : adj[i])
            std::cout << vertex.dest << "(" << vertex.weight << "), ";
        std::cout << "NULL" << std::endl;
    }
}