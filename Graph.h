#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <utility>

/* Graph edge data structure. */
struct Edge
{
    /* Source vertex of the edge. */
    int src;

    /* Destination vertex of the edge. */
    int dest;

    /* Weight of the edge. */
    int weight;

    // Constructor
    Edge(int source, int destination, int weight = 0) : src(source), dest(destination), weight(weight) {}

    // Custom graph Edge hash function tailored for adjacency lists.
    struct AdjListHash
    {
        std::size_t operator()(const Edge &e) const
        {
            // Only destination matters, as the source is always the same for the list.
            return std::hash<int>{}(e.dest);
        }
    };

    // Custom directed graph Edge comparison function
    struct DirectedEqual
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return (e1.src == e2.src && e1.dest == e2.dest);
        }
    };
};

/* Directed and weighted simple graph data structure. */
class Graph
{
    /* Vertices count. */
    int V;

    /* Pointer to an array containing adjacency lists. */
    std::unordered_set<Edge, Edge::AdjListHash, Edge::DirectedEqual> *adj;

public:
    /* Constructor for an empty graph with V vertices. */
    Graph(int V);

    /* Constructor for generating a random graph with V vertices and KMin-KMax edges per vertex. */
    Graph(int V, int KMinIn, int KMaxIn, int KMinOut, int KMaxOut);

    /* Constructor for initializing graph with a vector of edges. */
    Graph(int V, const std::vector<Edge> &edges);

    /* Destructor. */
    ~Graph();

    /* Add an edge to the graph. Returns true if insertion was successful. */
    bool addEdge(const Edge &edge);

    /* Remove an edge from the graph. Returns true if deletion was successful. */
    bool removeEdge(const Edge &edge);

    /* Check if an edge exists. */
    bool hasEdge(const Edge &edge) const;

    /* Print the graph's adjacency list. */
    void printGraph() const;

    /* Get the number of vertices in the graph. */
    int verticesCount() const { return V; }
};

#endif