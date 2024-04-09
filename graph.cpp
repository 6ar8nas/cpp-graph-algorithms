#include "utils.h"
#include "graph.h"
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

    adj = new std::unordered_set<Edge, Edge::AdjListHash, Edge::UndirectedEqual>[V];
}

bool Graph::HavelHakimi(const std::vector<int> &availableNeighbors) const
{
    // Copy the original vector to not change it during the check.
    std::vector<int> degrees(availableNeighbors);

    // Sort the degrees in non-increasing order
    std::sort(degrees.begin(), degrees.end(), std::greater<int>());

    while (!degrees.empty() || degrees[0] == 0)
    {
        // Remove the highest degree element
        int d = degrees[0];
        degrees.erase(degrees.begin());

        // Check if there are enough remaining vertices to connect to the removed vertex
        if (d >= degrees.size())
            return false;

        // Decrement each next 'd' highest degrees by 1
        for (int i = 0; i < d; ++i)
            --degrees[i];

        // Sort the remaining degrees for another loop.
        std::sort(degrees.begin(), degrees.end(), std::greater<int>());
    }

    return true;
}

Graph::Graph(int V, int KMin, int KMax) : Graph(V)
{
    if (KMax < KMin)
        throw std::invalid_argument("KMax must be greater than or equal to KMin.");

    if (KMin < 0 || KMax >= V)
        throw std::invalid_argument("Invalid range for number of neighbors.");

    if (KMin == KMax && KMin % 2 != 0 && V % 2 != 0)
        throw std::invalid_argument("It is impossible to form a graph from the given parameters.");

    // Generate a valid set of neighbors for each vertex.
    std::vector<int> availableNeighbors(V);
    int sum;
    int generatingAttempts = 0;
    std::uniform_int_distribution<int> randomNeighborCount(KMin, KMax);
    do
    {
        sum = 0;
        for (int &neighbor : availableNeighbors)
        {
            neighbor = randomNeighborCount(rng);
            sum += neighbor;
        }
    } while (sum % 2 != 0 && !HavelHakimi(availableNeighbors) && ++generatingAttempts < 20);

    if (generatingAttempts == 20)
        throw std::runtime_error("Failed to generate a valid set of neighbors for each vertex given the parameters.");

    std::uniform_int_distribution<int> randomVertex(0, V - 1);
    while (true)
    {
        // If all available neighbors are 0, prerequisites are met.
        if (std::all_of(availableNeighbors.begin(), availableNeighbors.end(), [](int n)
                        { return n == 0; }))
            return;

        int u = findIndexOfMax(availableNeighbors);
        bool performedAction = false;
        for (int i = 0, v = randomVertex(rng); i < 5 * V; ++i, v = (v + 1) % V)
        {
            if (u == v || availableNeighbors[v] == 0 || hasEdge(u, v))
                continue;

            // Add a preliminary edge to the graph.
            addEdge(u, v);
            --availableNeighbors[u];
            --availableNeighbors[v];

            performedAction = true;
            break;
        }

        while (!performedAction)
        {
            auto w = randomVertex(rng);
            // We're looking for an already filled vertex that we could remove and instead use for u.
            if (adj[w].empty() || hasEdge(u, w) || availableNeighbors[w] != 0 || u == w)
                continue;

            // Backtrack if no edge was added.
            auto iter = std::next(adj[w].begin(), std::uniform_int_distribution<int>(0, adj[w].size() - 1)(rng));
            int v = iter->dest;

            // Remove a random edge, as the graph cannot be completed with it.
            removeEdge(w, v);
            addEdge(u, w);
            ++availableNeighbors[v];
            --availableNeighbors[u];

            performedAction = true;
        }
    }
}

Graph::Graph(int V, const std::vector<Edge> &edges) : Graph(V)
{
    for (const auto &edge : edges)
        addEdge(edge.src, edge.dest);
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int u, int v)
{
    if (V <= u || V <= v)
        throw std::invalid_argument("The vertices must be within the range of the graph.");

    adj[u].insert(Edge(u, v));
    adj[v].insert(Edge(v, u));
}

void Graph::removeEdge(int u, int v)
{
    if (V <= u || V <= v)
        throw std::invalid_argument("The vertices must be within the range of the graph.");

    adj[u].erase(Edge(u, v));
    adj[v].erase(Edge(v, u));
}

bool Graph::hasEdge(int u, int v) const
{
    return adj[u].count(Edge(u, v)) != 0;
}

void Graph::printGraph() const
{
    for (int i = 0; i < V; ++i)
    {
        std::cout << i << " -> ";
        for (const auto &vertex : adj[i])
            std::cout << vertex.dest << ", ";
        std::cout << "NULL" << std::endl;
    }
}

int Graph::verticesCount() const
{
    return V;
}

bool Graph::isTree() const
{
    std::unordered_set<int> visited;
    std::unordered_map<int, int> parent;
    std::queue<int> queue;

    visited.insert(0);
    queue.push(0);
    parent[0] = -1;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        for (const auto &neighbor : adj[current])
        {
            if (visited.find(neighbor.dest) == visited.end())
            {
                visited.insert(neighbor.dest);
                queue.push(neighbor.dest);
                parent[neighbor.dest] = current;
            }
            else if (neighbor.dest != parent[current])
                return false;
        }
    }

    return visited.size() == V;
}