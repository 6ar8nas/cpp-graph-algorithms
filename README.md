# Graph Algorithms Coursework

## Overview

This repository contains coursework for the Graph Algorithms (2023/24) course, part of the Software Engineering program at Vilnius University.  
The primary focus is on implementation and analysis of various graph algorithms and data structures, with an emphasis on practical applications such as finding of a minimum spanning tree using Prim's algorithm, Dijkstra's algorithm and different Traveling Salesman Problem (TSP) heuristics.

## Features

### 1. Graph implementation

- The graph is an **undirected weighted graph**, implemented using an adjacency list.
- Graph includes constructors enabling randomized graph generation for both complete graph and a graph restricted to have exactly [KMin, KMax] edges for each vertex. 

### 2. Heap implementations

Repository includes **Fibonacci heap** and **Min-heap** data structures, implemented according to Cormen et al. `Introduction to Algorithms (Third edition)` respective documentation (chapters 6 and 19). Each heap implementation matches every presented example without any deviations from the expected step-by-step behavior.

#### Benchmarking

Both heaps have been benchmarked and compared in performance on matching graph setups using Dijkstra's algorithm. The benchmarking function is available in [`main.cpp`](./main.cpp). 

It can be [observed](./dijkstra-comparison.md), that while the Fibonacci heap in theory offers better time complexity for some heap operations, this advantage doesn't always translate into better performance. The Fibonacci heap appears to perform more efficiently as the graph size and graph density increases.

### 3. Traveling Salesman Problem (TSP) heuristics

Repository includes the following implemented heuristics for the Traveling Salesman Problem:

- **Nearest neighbor heuristic**: chooses the nearest unvisited vertex until all vertices are visited.
- **Double tree heuristic**: walks through consecutive unvisited Minimum Spanning Tree (MST) vertices. If an already visited vertex appears it is skipped in favor of the next unvisited MST node.
- **Random insertion heuristic**: a node to be included in the TSP is selected randomly and joined at a position, where the cost of inserting the new node in the already present TSP network is minimized.

#### Benchmarking

All three heuristics have been benchmarked and compared in performance on matching graph setups using the respective algorithms. The benchmarking function is available in [`main.cpp`](./main.cpp).

> Note: the algorithm for the double tree heuristic had to additionally iterate through the whole path to calculate the weight, while the other two heuristic algorithms incorporated that as a separate action inside the algorithm. This might have negatively impacted algorithm's performance metrics.

[Benchmarking metrics](./tsp-comparison.md) compare different heuristics computation duration and resulting path weight.

Overall, the nearest neighbor heuristic is the most performant, followed closely by the random insertion heuristic for small graphs (under 2500 vertices or 50 cities) and the double tree heuristic for larger graphs.

As for the TSP path weight, the random insertion heuristic has overall managed to find the cheapest traversal path under any graph sizes (with a small exception for very small graphs under 100 nodes), followed by the nearest neighbor (up to 10% higher) and double tree (up to 20% higher) heuristics respectively.

#### Visualization

To better understand the difference in heuristics behaviors, means for TSP path visualization have been composed using an open-source [Cairo](https://www.cairographics.org) graphics library.

The different cities are marked as dots (the starting city is marked blue, while all the others are red), while the edges are drawn as a black line. All of the points match their actual 2D position on the canvas.

Examples (same graph and starting node displayed):

- [Double tree](./double-tree-tsp-path.png)
- [Nearest neighbor](./nearest-neighbor-tsp-path.png)
- [Random insertion](./random-insertion-tsp-path.png)

> Note: While the graph and heap implementations do not require any prerequisites, visualization tools require a local Cairo distribution. Omit any `DrawingUtils.h` references to bypass this prerequisite.