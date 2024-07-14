#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <utility>
#include <iostream>

// Edge represents a connection between two vertices in a graph.
// Implemented for undirected graphs.
struct Edge
{
    int src;
    int dest;
    int weight;

    Edge(int source, int destination, int weight = 0) : src(source), dest(destination), weight(weight) {}

    bool operator==(const Edge &other) const
    {
        return weight == other.weight && ((src == other.src && dest == other.dest) ||
                                          (src == other.dest && dest == other.src));
    }

    // In adjacency list, the source is always the same, so hashing only the destination is better performance-wise.
    struct AdjListHash
    {
        std::size_t operator()(const Edge &e) const
        {
            return std::hash<int>{}(e.dest);
        }
    };

    struct AdjListEquals
    {
        bool operator()(const Edge &e1, const Edge &e2) const
        {
            return (e1.src == e2.src && e1.dest == e2.dest) || (e1.src == e2.dest && e1.dest == e2.src);
        }
    };
};

// City represents a point in a 2D plane. City mesh can be mapped to a graph.
struct City
{
    int index;
    int x, y;

    City(int index, int x, int y) : index(index), x(x), y(y) {}

    double distance(const City &other) const
    {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    static std::unordered_map<int, City> generateRandomGraphCities(int n);
};

// VertexInfo represents a vertex in a graph with additional information for algorithms and traversals.
// Separate VertexInfo objects can be uniquely identified by its vertex property.
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
        os << obj.vertex << " (p = " << obj.parent << ", d = " << obj.distance << ")";
        return os;
    }

    struct VertexHash
    {
        std::size_t operator()(const VertexInfo &vi) const
        {
            return std::hash<int>()(vi.vertex);
        }
    };

    struct VertexEquals
    {
        bool operator()(const VertexInfo &lhs, const VertexInfo &rhs) const
        {
            return lhs.vertex == rhs.vertex;
        }
    };
};

// Graph represents a collection of vertices and edges.
// Implemented for undirected graphs.
class Graph
{
private:
    int V;
    std::unordered_set<Edge, Edge::AdjListHash, Edge::AdjListEquals> *adj;

public:
    // Random weighted complete graph generator.
    Graph(int V);
    // Random weighted graph generator with edge count for each vertex in range [KMin, KMax].
    Graph(int V, int KMin, int KMax);
    Graph(int V, const std::vector<Edge> &edges);
    Graph(const std::unordered_map<int, City> &cities);
    ~Graph() { delete[] adj; }

    bool addEdge(const Edge &edge);
    bool removeEdge(const Edge &edge);
    bool hasEdge(const Edge &edge) const;
    int verticesCount() const { return V; }

    std::pair<std::unordered_map<int, VertexInfo>, double> dijkstraMinHeap(int sourceKey) const;
    std::pair<std::unordered_map<int, VertexInfo>, double> dijkstraFibHeap(int sourceKey) const;
    static void printDijkstraResults(int source, const std::unordered_map<int, VertexInfo> &distances);

    std::vector<VertexInfo> primMST(int start) const;
    std::vector<int> preorderWalk(const std::vector<VertexInfo> &mst) const;

    std::pair<std::pair<std::vector<int>, int>, double> nearestNeighborTSP(int start) const;
    std::pair<std::pair<std::vector<int>, int>, double> doubleTreeTSP(int start) const;
    std::pair<std::pair<std::vector<int>, int>, double> randomInsertionTSP(int start1, int start2) const;

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

#endif // GRAPH_H