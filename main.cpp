#include "Graph.h"
#include "DrawingUtils.h"
#include <iostream>
#include <chrono>

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    auto citiesCount = 1000;
    std::unordered_map<int, City> cities = City::generateRandomGraphCities(citiesCount);
    Graph graph(cities);
    std::chrono::duration<double> durationGen = std::chrono::high_resolution_clock::now() - start_time;

    auto doubleTree = graph.doubleTreeTSP(0);
    std::cout << "Double tree TSP weight = " << doubleTree.first.second << " duration = " << doubleTree.second << " seconds" << std::endl;
    drawPathTSP(cities, doubleTree.first.first, "Double tree");

    auto nearestNeighbors = graph.nearestNeighborTSP(0);
    std::cout << "Nearest neighbor TSP weight = " << nearestNeighbors.first.second << " duration = " << nearestNeighbors.second << " seconds" << std::endl;
    drawPathTSP(cities, nearestNeighbors.first.first, "Nearest neighbor");

    auto randomInsertion = graph.randomInsertionTSP(0, 1);
    std::cout << "Random insertion TSP weight = " << randomInsertion.first.second << " duration = " << randomInsertion.second << " seconds" << std::endl;
    drawPathTSP(cities, randomInsertion.first.first, "Random insertion");

    return 0;
}

int benchmarkTSP()
{
    int citiesCount = 25000;
    int attempts = 1;

    double totalDurationGen = 0;
    double totalDoubleTreeDuration = 0;
    int totalDoubleTreeWeights = 0;
    double totalNearestNeighborDuration = 0;
    int totalNearestNeighborWeights = 0;
    double totalRandomInsertionDuration = 0;
    int totalRandomInsertionWeights = 0;

    for (int i = 0; i < attempts; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::unordered_map<int, City> cities = City::generateRandomGraphCities(citiesCount);
        Graph graph(cities);
        std::chrono::duration<double> durationGen = std::chrono::high_resolution_clock::now() - start_time;
        totalDurationGen += durationGen.count();

        auto doubleTree = graph.doubleTreeTSP(0);
        totalDoubleTreeDuration += doubleTree.second;
        totalDoubleTreeWeights += doubleTree.first.second;

        auto nearestNeighbors = graph.nearestNeighborTSP(0);
        totalNearestNeighborDuration += nearestNeighbors.second;
        totalNearestNeighborWeights += nearestNeighbors.first.second;

        auto randomInsertion = graph.randomInsertionTSP(0, 1);
        totalRandomInsertionDuration += randomInsertion.second;
        totalRandomInsertionWeights += randomInsertion.first.second;
    }

    std::cout << "Cities count: " << citiesCount << ", attempts: " << attempts << std::endl;
    std::cout << "Average graph gen. duration: " << totalDurationGen / attempts << std::endl;
    std::cout << "Average double tree algorithm duration = " << totalDoubleTreeDuration / attempts << ", weights = " << totalDoubleTreeWeights / attempts << std::endl;
    std::cout << "Average nearest neighbor algorithm duration = " << totalNearestNeighborDuration / attempts << ", weights = " << totalNearestNeighborWeights / attempts << std::endl;
    std::cout << "Average random insertion algorithm duration = " << totalRandomInsertionDuration / attempts << ", weights = " << totalRandomInsertionWeights / attempts << std::endl;

    return 0;
}

int benchmarkDijkstra()
{
    int nodeCount = 1000;
    int kMin = 0;
    int kMax = 50;
    int attempts = 1000;

    double totalDurationGen = 0;
    double totalMinHeapDuration = 0;
    double totalFibHeapDuration = 0;
    for (int i = 0; i < attempts; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        Graph gen(nodeCount, kMin, kMax);
        std::chrono::duration<double> durationGen = std::chrono::high_resolution_clock::now() - start_time;
        totalDurationGen += durationGen.count();
        auto minHeap = gen.dijkstraMinHeap(0);
        totalMinHeapDuration += minHeap.second;
        auto fibHeap = gen.dijkstraFibHeap(0);
        totalFibHeapDuration += fibHeap.second;
    }

    std::cout << "Node count: " << nodeCount << ", gen. boundaries: [" << kMin << ", " << kMax << "], attempts: " << attempts << std::endl;
    std::cout << "Average graph gen. duration: " << totalDurationGen / attempts << std::endl;
    std::cout << "Average minimum heap Dijkstra duration = " << totalMinHeapDuration / attempts << std::endl;
    std::cout << "Average fibonacci heap Dijkstra duration = " << totalFibHeapDuration / attempts << std::endl;

    return 0;
}