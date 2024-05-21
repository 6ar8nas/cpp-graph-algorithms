#include "Graph.h"
#include "DrawingUtils.h"
#include <iostream>
#include <chrono>

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    auto citiesCount = 1000;
    std::unordered_map<int, City> cities = generateRandomGraphCities(citiesCount);
    Graph graph(cities);
    std::chrono::duration<double> durationGen = std::chrono::high_resolution_clock::now() - start_time;
    // std::cout << "Full graph of " << citiesCount << " cities created in " << durationGen.count() << " seconds" << std::endl;
    // std::cout << graph << std::endl;

    auto doubleTree = graph.doubleTreeTSP(0);
    // std::cout << "Double tree TSP path:" << std::endl;
    // for (auto vertex : doubleTree.first.first)
    //     std::cout << vertex << " -> ";
    // std::cout << "END" << std::endl;
    std::cout << "Double tree TSP weight = " << doubleTree.first.second << " duration = " << doubleTree.second << " seconds" << std::endl;
    drawPathTSP(cities, doubleTree.first.first, "Double tree");

    auto nearestNeighbors = graph.nearestNeighborTSP(0);
    // std::cout << "Nearest neighbor TSP path:" << std::endl;
    // for (auto vertex : nearestNeighbors.first.first)
    //     std::cout << vertex << " -> ";
    // std::cout << "END" << std::endl;
    std::cout << "Nearest neighbor TSP weight = " << nearestNeighbors.first.second << " duration = " << nearestNeighbors.second << " seconds" << std::endl;
    drawPathTSP(cities, nearestNeighbors.first.first, "Nearest neighbor");

    auto randomInsertion = graph.randomInsertionTSP(0, 1);
    // std::cout << "Random insertion TSP path:" << std::endl;
    // for (auto vertex : randomInsertion.first.first)
    //     std::cout << vertex << " -> ";
    // std::cout << "END" << std::endl;
    std::cout << "Random insertion TSP weight = " << randomInsertion.first.second << " duration = " << randomInsertion.second << " seconds" << std::endl;
    drawPathTSP(cities, randomInsertion.first.first, "Random insertion");

    return 0;
}

int benchmark()
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
        std::unordered_map<int, City> cities = generateRandomGraphCities(citiesCount);
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
    std::cout << "Avg graph creation duration: " << totalDurationGen / attempts << std::endl;
    std::cout << "Avg double tree duration = " << totalDoubleTreeDuration / attempts << ", weights = " << totalDoubleTreeWeights / attempts << std::endl;
    std::cout << "Avg nearest neighbor duration = " << totalNearestNeighborDuration / attempts << ", weights = " << totalNearestNeighborWeights / attempts << std::endl;
    std::cout << "Avg random insertion duration = " << totalRandomInsertionDuration / attempts << ", weights = " << totalRandomInsertionWeights / attempts << std::endl;

    return 0;
}