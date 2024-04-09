#include "graph.h"
#include <vector>
#include <iostream>
#include <chrono>

int main()
{
    // std::vector<Edge> edges2 = {{0, 1}, {1, 2}, {2, 3}, {2, 4}};
    // Graph g2(5, edges2);
    // std::cout << "Graph g2 with 5 vertices and predefined edges:" << std::endl;
    // g2.printGraph();
    // std::cout << "Graph g2 is" << (g2.isTree() ? "" : " not") << " a tree." << std::endl;
    // std::cout << "Adding an edge to graph g2 between vertices 2 and 0 to create a cycle 0 - 1 - 2." << std::endl;
    // g2.addEdge(2, 0);
    // std::cout << "Updated v2 graph g2 is" << (g2.isTree() ? "" : " not") << " a tree." << std::endl;
    // std::cout << "Removing an edge from graph g2 between vertices 1 and 0 to remove the cycle." << std::endl;
    // g2.removeEdge(1, 0);
    // std::cout << "Updated v3 graph g2 is" << (g2.isTree() ? "" : " not") << " a tree." << std::endl;
    // std::cout << std::endl;

    // std::vector<Edge> edges3 = {{14, 3}, {14, 8}, {14, 29}, {3, 45}, {3, 24}, {8, 13}, {29, 49}, {29, 36}, {45, 0}, {45, 16}, {24, 11}, {24, 34}, {13, 6}, {13, 18}, {49, 21}, {49, 25}, {36, 26}, {36, 4}, {0, 37}, {0, 44}, {16, 31}, {16, 27}, {11, 32}, {11, 10}, {34, 35}, {34, 12}, {6, 42}, {6, 2}, {18, 33}, {18, 41}, {21, 28}, {21, 1}, {25, 7}, {25, 20}, {26, 5}, {26, 38}, {4, 39}, {4, 48}, {37, 15}, {37, 46}, {44, 17}, {44, 19}, {31, 47}, {27, 30}, {32, 43}, {10, 9}, {35, 23}, {12, 22}, {42, 40}, {2, 15}, {33, 19}, {41, 22}, {28, 47}, {1, 30}, {7, 5}, {20, 38}, {5, 40}, {38, 9}, {39, 23}, {48, 17}};
    // Graph g3(50, edges3);
    // std::cout << "Graph g3 with 50 vertices and predefined edges:" << std::endl;
    // g3.printGraph();
    // std::cout << "Graph g3 is" << (g2.isTree() ? "" : " not") << " a tree." << std::endl;
    // std::cout << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    Graph g6(20000, 3, 6);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Graph g6 with 100000 vertices and random edges between 1 and 100 per vertex:" << std::endl;
    g6.printGraph();
    std::cout << "Graph g6 is" << (g6.isTree() ? "" : " not") << " a tree." << std::endl;
    std::cout << "Generating time: " << duration.count() << " seconds" << std::endl;
    std::cout << std::endl;

    return 0;
}
