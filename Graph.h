#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <utility>
#include <iostream>

struct Edge
{
    int src;
    int dest;
    int weight;

    Edge(int source, int destination, int weight = 0) : src(source), dest(destination), weight(weight) {}

    struct AdjListHash
    {
        std::size_t operator()(const Edge &e) const
        {
            return std::hash<int>{}(e.dest);
        }
    };

    struct DirectedEqual
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return (e1.src == e2.src && e1.dest == e2.dest);
        }
    };
};

class VertexInfo
{
public:
    int vertex;
    int distance;
    int parent;
    bool isRemoved;

    VertexInfo(int vertex, int distance, int parent) : vertex(vertex), distance(distance), parent(parent), isRemoved(false) {}

    friend bool operator>(const VertexInfo &lhs, const VertexInfo &rhs)
    {
        return lhs.distance > rhs.distance;
    }

    friend bool operator<(const VertexInfo &lhs, const VertexInfo &rhs)
    {
        return lhs.distance < rhs.distance;
    }

    friend std::ostream &operator<<(std::ostream &os, const VertexInfo &obj)
    {
        os << obj.vertex << " (d = " << obj.distance << ", p = " << obj.parent << ")";
        return os;
    }

    struct DijkstraHash
    {
        std::size_t operator()(const VertexInfo &vi) const
        {
            return std::hash<int>()(vi.vertex);
        }
    };

    struct DijkstraEqual
    {
        bool operator()(const VertexInfo &lhs, const VertexInfo &rhs) const
        {
            return lhs.vertex == rhs.vertex;
        }
    };
};

class Graph
{
private:
    int V;
    std::unordered_set<Edge, Edge::AdjListHash, Edge::DirectedEqual> *adj;

public:
    Graph(int V);
    Graph(int V, int KMinIn, int KMaxIn, int KMinOut, int KMaxOut);
    Graph(int V, const std::vector<Edge> &edges);
    ~Graph();
    bool addEdge(const Edge &edge);
    bool removeEdge(const Edge &edge);
    bool hasEdge(const Edge &edge) const;
    int verticesCount() const { return V; }

    std::pair<std::unordered_map<int, VertexInfo>, double> dijkstraMinHeap(int sourceKey) const;
    std::pair<std::unordered_map<int, VertexInfo>, double> dijkstraFibHeap(int sourceKey) const;
    static void printDijkstraResults(int source, const std::unordered_map<int, VertexInfo> &distances, double duration);

    friend std::ostream &operator<<(std::ostream &os, const Graph &obj)
    {
        for (int i = 0; i < obj.V; ++i)
        {
            os << i << " -> ";
            for (const auto &vertex : obj.adj[i])
                os << vertex.dest << "(" << vertex.weight << "), ";
            os << "NULL" << std::endl;
        }
        return os;
    }
};

#endif