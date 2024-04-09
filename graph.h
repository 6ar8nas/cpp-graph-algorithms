#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>

/* Unweighted graph edge data structure. */
struct Edge
{
    /* Source vertex of the edge. */
    int src;

    /* Destination vertex of the edge. */
    int dest;

    // Custom generic undirected graph Edge hash function
    struct UndirectedHash
    {
        std::size_t operator()(const Edge &e) const
        {
            // Ensure order doesn't matter
            int val1 = std::min(e.src, e.dest);
            int val2 = std::max(e.src, e.dest);
            // Combine hashes of x and y
            return std::hash<int>()(val1) ^ std::hash<int>()(val2);
        }
    };

    // Custom adjacency list tailored undirected graph Edge hash function
    struct AdjListHash
    {
        std::size_t operator()(const Edge &e) const
        {
            // The source is always the same, so we only care about destination.
            return std::hash<int>()(e.dest);
        }
    };

    // Custom undirected graph Edge comparison function
    struct UndirectedEqual
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            // Order doesn't matter here
            return (e1.src == e2.src && e1.dest == e2.dest) || (e1.src == e2.dest && e1.dest == e2.src);
        }
    };

    // Constructor
    Edge(int source, int destination) : src(source), dest(destination) {}
};

/* Undirected and unweighted simple graph data structure. */
class Graph
{
    /* Vertices count. */
    int V;

    /* Pointer to an array containing adjacency lists. */
    std::unordered_set<Edge, Edge::AdjListHash, Edge::UndirectedEqual> *adj;

    /* Havel-Hakimi algorithm for checking if a sequence of degrees is graphical. */
    bool HavelHakimi(const std::vector<int> &availableNeighbors) const;

public:
    /* Constructor for an empty graph with V vertices. */
    Graph(int V);

    /* Constructor for generating a random graph with V vertices and KMin-KMax edges per vertex. */
    Graph(int V, int KMin, int KMax);

    /* Constructor for initializing graph with a vector of edges. */
    Graph(int V, const std::vector<Edge> &edges);

    /* Destructor. */
    ~Graph();

    /* Add an undirected edge to the graph. */
    void addEdge(int u, int v);

    /* Remove an undirected edge from the graph if it exists. */
    void removeEdge(int u, int v);

    /* Check if an edge exists between vertices u and v. */
    bool hasEdge(int u, int v) const;

    /* Print the graph's adjacency list. */
    void printGraph() const;

    /* Get the number of vertices in the graph. */
    int verticesCount() const;

    /* Checks whether the graph is a tree (fully connected and has non-cyclic). */
    bool isTree() const;
};

#endif