#include "Graph.h"
#include "MinHeap.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <stack>

std::random_device dev;
std::mt19937 rng(dev());

Graph::Graph(int V) : V(V)
{
    if (V < 0)
        throw std::invalid_argument("The number of vertices must be non-negative.");

    adj = new std::unordered_set<Edge, Edge::AdjListHash, Edge::AdjListEquals>[V];

    std::uniform_int_distribution<int> weight(1, 50);

    for (int i = 0; i < V - 1; ++i)
    {
        for (int j = i + 1; j < V; ++j)
        {
            int edgeWeight = weight(rng);
            addEdge({i, j, edgeWeight});
        }
    }
}

Graph::Graph(const std::unordered_map<int, City> &cities) : V(cities.size())
{
    adj = new std::unordered_set<Edge, Edge::AdjListHash, Edge::AdjListEquals>[V];

    for (int i = 0; i < V - 1; ++i)
    {
        for (int j = i + 1; j < V; ++j)
        {
            double dist = cities.at(i).distance(cities.at(j));
            int edgeWeight = static_cast<int>(dist);
            addEdge({i, j, edgeWeight});
        }
    }
}

Graph::Graph(int V, const std::vector<Edge> &edges) : V(V)
{
    if (V < 0)
        throw std::invalid_argument("The number of vertices must be non-negative.");

    adj = new std::unordered_set<Edge, Edge::AdjListHash, Edge::AdjListEquals>[V];

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

    if (adj[edge.src].insert(edge).second)
    {
        adj[edge.dest].insert(Edge(edge.dest, edge.src, edge.weight));
        return true;
    }
    return false;
}

bool Graph::removeEdge(const Edge &edge)
{
    if (V <= edge.src || V <= edge.dest)
        throw std::invalid_argument("The vertices must be within the range of the graph.");

    if (adj[edge.src].erase(edge))
    {
        adj[edge.dest].erase(Edge(edge.dest, edge.src, edge.weight));
        return true;
    }
    return false;
}

bool Graph::hasEdge(const Edge &edge) const
{
    return adj[edge.src].count(edge) != 0;
}

std::vector<VertexInfo> Graph::primMST(int start) const
{
    std::vector<VertexInfo> mst;

    auto maxValue = std::numeric_limits<int>::max() / 2;
    std::vector<VertexInfo> vertices;
    for (int i = 0; i < V; ++i)
        vertices.emplace_back(VertexInfo(i, (i == start ? 0 : maxValue), -1));

    MinHeap<VertexInfo, VertexInfo::VertexHash, VertexInfo::VertexEquals> minHeap(vertices);
    while (!minHeap.isEmpty())
    {
        VertexInfo u = minHeap.extractMin();
        vertices.at(u.vertex).isRemoved = true;
        mst.push_back(u);

        for (const auto &edge : adj[u.vertex])
        {
            if (vertices.at(edge.dest).isRemoved)
                continue;

            int adjVertex = edge.dest;
            if (edge.weight < vertices.at(adjVertex).distance)
            {
                vertices.at(adjVertex).parent = u.vertex;
                vertices.at(adjVertex).distance = edge.weight;
                minHeap.decreaseKey(vertices.at(adjVertex), VertexInfo(adjVertex, edge.weight, u.vertex));
            }
        }
    }

    return mst;
}

std::vector<int> Graph::preorderWalk(const std::vector<VertexInfo> &mst) const
{
    std::vector<int> preorder;
    if (mst.empty())
        return preorder;

    std::vector<std::vector<int>> tree(V);
    for (const auto &info : mst)
    {
        if (info.parent == -1)
            continue;

        tree[info.parent].push_back(info.vertex);
    }

    std::vector<bool> visited(V, false);
    std::stack<int> stack;

    stack.push(mst[0].vertex);
    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        if (!visited[current])
        {
            visited[current] = true;
            preorder.push_back(current);

            for (auto it = tree[current].rbegin(); it != tree[current].rend(); ++it)
            {
                if (!visited[*it])
                    stack.push(*it);
            }
        }
    }

    return preorder;
}

std::pair<std::pair<std::vector<int>, int>, double> Graph::nearestNeighborTSP(int start) const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<int> tour;
    int totalWeight = 0;
    std::vector<bool> visited(V, false);
    int current = start;
    tour.push_back(current);
    visited[current] = true;

    for (int i = 1; i < V; ++i)
    {
        int minWeight = std::numeric_limits<int>::max();
        int nextEdge;
        for (const auto &edge : adj[current])
        {
            if (!visited[edge.dest] && edge.weight < minWeight)
            {
                minWeight = edge.weight;
                nextEdge = edge.dest;
            }
        }
        tour.push_back(nextEdge);
        totalWeight += minWeight;
        visited[nextEdge] = true;
        current = nextEdge;
    }

    tour.push_back(start);
    totalWeight += adj[current].find({current, start})->weight;

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    return std::make_pair(std::make_pair(tour, totalWeight), duration.count());
}

std::pair<std::pair<std::vector<int>, int>, double> Graph::doubleTreeTSP(int start) const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<VertexInfo> mst = primMST(start);
    std::vector<int> preorder = preorderWalk(mst);

    preorder.push_back(preorder.front());

    int totalWeight = 0;
    for (auto i = 0; i < preorder.size() - 1; ++i)
    {
        int u = preorder[i];
        int v = preorder[i + 1];

        auto it = std::find_if(adj[u].begin(), adj[u].end(), [v](const Edge &e)
                               { return e.dest == v; });

        if (it != adj[u].end())
            totalWeight += it->weight;
    }

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    return std::make_pair(std::make_pair(preorder, totalWeight), duration.count());
}

std::pair<std::pair<std::vector<int>, int>, double> Graph::randomInsertionTSP(int start1, int start2) const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<int> tour;
    tour.push_back(start1);
    tour.push_back(start2);

    int totalWeight = adj[start1].find({start1, start2, 0})->weight;

    std::vector<int> unvisited;
    for (auto i = 0; i < V; ++i)
    {
        if (i == start1 || i == start2)
            continue;

        unvisited.push_back(i);
    }

    while (!unvisited.empty())
    {
        int randIndex = rand() % unvisited.size();
        int newVertex = unvisited[randIndex];
        unvisited.erase(unvisited.begin() + randIndex);

        int bestDiff = std::numeric_limits<int>::max();
        int insertIndex = -1;
        for (auto i = 1; i < tour.size(); ++i)
        {
            int u = tour[i - 1];
            int v = tour[i];

            int diff = adj[u].find({u, newVertex, 0})->weight + adj[newVertex].find({newVertex, v, 0})->weight - adj[u].find({u, v, 0})->weight;
            if (diff < bestDiff)
            {
                bestDiff = diff;
                insertIndex = i;
            }
        }

        tour.insert(tour.begin() + insertIndex, newVertex);
        totalWeight += bestDiff;
    }

    totalWeight += adj[tour.back()].find({tour.back(), tour.front(), 0})->weight;
    tour.push_back(tour.front());

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    return std::make_pair(std::make_pair(tour, totalWeight), duration.count());
}

std::unordered_map<int, City> City::generateRandomGraphCities(int n)
{
    std::unordered_map<int, City> cities;
    std::uniform_int_distribution<int> coordinate(0, 2000);

    for (int i = 0; i < n; ++i)
        cities.insert({i, City(i, coordinate(rng), coordinate(rng))});

    return cities;
}
