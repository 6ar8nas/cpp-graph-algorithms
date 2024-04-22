#include "Graph.h"
#include "FibonacciHeap.h"
#include "MinHeap.h"
#include <iostream>

int main()
{
    // // Dijkstra testing on generated graph
    // {
    //     auto start_time1 = std::chrono::high_resolution_clock::now();
    //     Graph gen10m(10000000, 0, 3, 0, 3);
    //     std::cout << "Graph gen10m with 10000000 vertices and random 0-3 edges" << std::endl;
    //     // std::cout << gen10m << std::endl;
    //     std::chrono::duration<double> duration1 = std::chrono::high_resolution_clock::now() - start_time1;
    //     std::cout << duration1.count() << std::endl;
    // }
    // {
    //     auto start_time2 = std::chrono::high_resolution_clock::now();
    //     Graph gen1m(1000000, 0, 10, 0, 10);
    //     std::cout << "Graph gen1m with 1000000 vertices and random 0-10 edges" << std::endl;
    //     // std::cout << gen1m << std::endl;
    //     std::chrono::duration<double> duration2 = std::chrono::high_resolution_clock::now() - start_time2;
    //     std::cout << duration2.count() << std::endl;
    // }
    // {
    //     auto start_time3 = std::chrono::high_resolution_clock::now();
    //     Graph gen100k(100000, 0, 100, 0, 100);
    //     std::cout << "Graph gen100k with 100000 vertices and random 0-100 edges" << std::endl;
    //     // std::cout << gen100k << std::endl;
    //     std::chrono::duration<double> duration3 = std::chrono::high_resolution_clock::now() - start_time3;
    //     std::cout << duration3.count() << std::endl;
    // }
    // {
    //     auto start_time4 = std::chrono::high_resolution_clock::now();
    //     Graph gen10k(10000, 0, 1000, 0, 1000);
    //     std::cout << "Graph gen10k with 10000 vertices and random 0-1000 edges" << std::endl;
    //     // std::cout << gen10k << std::endl;
    //     std::chrono::duration<double> duration4 = std::chrono::high_resolution_clock::now() - start_time4;
    //     std::cout << duration4.count() << std::endl;
    // }
    // {
    //     auto start_time5 = std::chrono::high_resolution_clock::now();
    //     Graph gen5k(5000, 1000, 4999, 1000, 4999);
    //     std::cout << "Graph gen5k with 5000 vertices and random 1000-4999 edges" << std::endl;
    //     // std::cout << gen5k << std::endl;
    //     std::chrono::duration<double> duration5 = std::chrono::high_resolution_clock::now() - start_time5;
    //     std::cout << duration5.count() << std::endl;
    // }
    // {
    //     auto start_time6 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k1(1000, 0, 5, 0, 5);
    //     std::cout << "Graph gen1k1 with 1000 vertices and random 0-5 edges" << std::endl;
    //     // std::cout << gen1k1 << std::endl;
    //     std::chrono::duration<double> duration6 = std::chrono::high_resolution_clock::now() - start_time6;
    //     std::cout << duration6.count() << std::endl;
    // }
    // {
    //     auto start_time7 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k2(1000, 0, 25, 0, 25);
    //     std::cout << "Graph gen1k2 with 1000 vertices and random 0-25 edges" << std::endl;
    //     // std::cout << gen1k2 << std::endl;
    //     std::chrono::duration<double> duration7 = std::chrono::high_resolution_clock::now() - start_time7;
    //     std::cout << duration7.count() << std::endl;
    // }
    // {
    //     auto start_time8 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k3(1000, 0, 50, 0, 50);
    //     std::cout << "Graph gen1k3 with 1000 vertices and random 0-50 edges" << std::endl;
    //     // std::cout << gen1k3 << std::endl;
    //     std::chrono::duration<double> duration8 = std::chrono::high_resolution_clock::now() - start_time8;
    //     std::cout << duration8.count() << std::endl;
    // }
    // {
    //     auto start_time9 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k4(1000, 0, 100, 0, 100);
    //     std::cout << "Graph gen1k4 with 1000 vertices and random 0-100 edges" << std::endl;
    //     // std::cout << gen1k4 << std::endl;
    //     std::chrono::duration<double> duration9 = std::chrono::high_resolution_clock::now() - start_time9;
    //     std::cout << duration9.count() << std::endl;
    // }
    // {
    //     auto start_time10 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k5(1000, 0, 200, 0, 200);
    //     std::cout << "Graph gen1k5 with 1000 vertices and random 0-200 edges" << std::endl;
    //     // std::cout << gen1k5 << std::endl;
    //     std::chrono::duration<double> duration10 = std::chrono::high_resolution_clock::now() - start_time10;
    //     std::cout << duration10.count() << std::endl;
    // }
    // {
    //     auto start_time11 = std::chrono::high_resolution_clock::now();
    //     Graph gen1k6(1000, 0, 500, 0, 500);
    //     std::cout << "Graph gen1k6 with 1000 vertices and random 0-500 edges" << std::endl;
    //     // std::cout << gen1k6 << std::endl;
    //     std::chrono::duration<double> duration11 = std::chrono::high_resolution_clock::now() - start_time11;
    //     std::cout << duration11.count() << std::endl;
    // }

    // // Fibonacci heap testing
    // {
    //     FibonacciHeapNode<int> *fibExtractNode1 = new FibonacciHeapNode<int>(23);
    //     FibonacciHeapNode<int> *fibExtractNode2 = new FibonacciHeapNode<int>(7);
    //     FibonacciHeapNode<int> *fibExtractNode3 = new FibonacciHeapNode<int>(21);
    //     FibonacciHeapNode<int> *fibExtractNode4 = new FibonacciHeapNode<int>(3);
    //     FibonacciHeapNode<int> *fibExtractNode41 = new FibonacciHeapNode<int>(18);
    //     FibonacciHeapNode<int> *fibExtractNode411 = new FibonacciHeapNode<int>(39);
    //     FibonacciHeapNode<int> *fibExtractNode42 = new FibonacciHeapNode<int>(52);
    //     FibonacciHeapNode<int> *fibExtractNode43 = new FibonacciHeapNode<int>(38);
    //     FibonacciHeapNode<int> *fibExtractNode431 = new FibonacciHeapNode<int>(41);
    //     FibonacciHeapNode<int> *fibExtractNode5 = new FibonacciHeapNode<int>(17);
    //     FibonacciHeapNode<int> *fibExtractNode51 = new FibonacciHeapNode<int>(30);
    //     FibonacciHeapNode<int> *fibExtractNode6 = new FibonacciHeapNode<int>(24);
    //     FibonacciHeapNode<int> *fibExtractNode61 = new FibonacciHeapNode<int>(26);
    //     FibonacciHeapNode<int> *fibExtractNode611 = new FibonacciHeapNode<int>(35);
    //     FibonacciHeapNode<int> *fibExtractNode62 = new FibonacciHeapNode<int>(46);

    //     fibExtractNode1->right = fibExtractNode2;
    //     fibExtractNode1->left = fibExtractNode6;
    //     fibExtractNode2->right = fibExtractNode3;
    //     fibExtractNode2->left = fibExtractNode1;
    //     fibExtractNode3->right = fibExtractNode4;
    //     fibExtractNode3->left = fibExtractNode2;
    //     fibExtractNode4->right = fibExtractNode5;
    //     fibExtractNode4->left = fibExtractNode3;
    //     fibExtractNode4->child = fibExtractNode41;
    //     fibExtractNode4->degree = 3;
    //     fibExtractNode41->right = fibExtractNode42;
    //     fibExtractNode41->left = fibExtractNode43;
    //     fibExtractNode41->parent = fibExtractNode4;
    //     fibExtractNode41->child = fibExtractNode411;
    //     fibExtractNode41->isMarked = true;
    //     fibExtractNode41->degree = 1;
    //     fibExtractNode411->parent = fibExtractNode41;
    //     fibExtractNode411->isMarked = true;
    //     fibExtractNode42->right = fibExtractNode43;
    //     fibExtractNode42->left = fibExtractNode41;
    //     fibExtractNode42->parent = fibExtractNode4;
    //     fibExtractNode43->right = fibExtractNode41;
    //     fibExtractNode43->left = fibExtractNode42;
    //     fibExtractNode43->child = fibExtractNode431;
    //     fibExtractNode43->parent = fibExtractNode4;
    //     fibExtractNode43->degree = 1;
    //     fibExtractNode431->parent = fibExtractNode43;
    //     fibExtractNode5->right = fibExtractNode6;
    //     fibExtractNode5->left = fibExtractNode4;
    //     fibExtractNode5->child = fibExtractNode51;
    //     fibExtractNode5->degree = 1;
    //     fibExtractNode51->parent = fibExtractNode5;
    //     fibExtractNode6->right = fibExtractNode1;
    //     fibExtractNode6->left = fibExtractNode5;
    //     fibExtractNode6->child = fibExtractNode61;
    //     fibExtractNode6->degree = 2;
    //     fibExtractNode61->right = fibExtractNode62;
    //     fibExtractNode61->left = fibExtractNode62;
    //     fibExtractNode61->child = fibExtractNode611;
    //     fibExtractNode61->isMarked = true;
    //     fibExtractNode61->degree = 1;
    //     fibExtractNode611->parent = fibExtractNode61;
    //     fibExtractNode62->right = fibExtractNode61;
    //     fibExtractNode62->left = fibExtractNode61;

    //     FibonacciHeap<int> extractMinFibHeap(fibExtractNode4, 15);
    //     std::cout << "Initial state of 514p extract min example:" << std::endl;
    //     std::cout << extractMinFibHeap << std::endl;
    //     auto minElement = extractMinFibHeap.extractMin();
    //     std::cout << "minElement: " << minElement << std::endl;
    //     std::cout << "State after extract min: " << std::endl;
    //     std::cout << extractMinFibHeap << std::endl;

    //     FibonacciHeapNode<int> *fibDecreaseNode1 = new FibonacciHeapNode<int>(7);
    //     FibonacciHeapNode<int> *fibDecreaseNode11 = new FibonacciHeapNode<int>(24);
    //     FibonacciHeapNode<int> *fibDecreaseNode111 = new FibonacciHeapNode<int>(26);
    //     FibonacciHeapNode<int> *fibDecreaseNode1111 = new FibonacciHeapNode<int>(35);
    //     FibonacciHeapNode<int> *fibDecreaseNode112 = new FibonacciHeapNode<int>(46);
    //     FibonacciHeapNode<int> *fibDecreaseNode12 = new FibonacciHeapNode<int>(17);
    //     FibonacciHeapNode<int> *fibDecreaseNode121 = new FibonacciHeapNode<int>(30);
    //     FibonacciHeapNode<int> *fibDecreaseNode13 = new FibonacciHeapNode<int>(23);
    //     FibonacciHeapNode<int> *fibDecreaseNode2 = new FibonacciHeapNode<int>(18);
    //     FibonacciHeapNode<int> *fibDecreaseNode21 = new FibonacciHeapNode<int>(21);
    //     FibonacciHeapNode<int> *fibDecreaseNode211 = new FibonacciHeapNode<int>(52);
    //     FibonacciHeapNode<int> *fibDecreaseNode22 = new FibonacciHeapNode<int>(39);
    //     FibonacciHeapNode<int> *fibDecreaseNode3 = new FibonacciHeapNode<int>(38);
    //     FibonacciHeapNode<int> *fibDecreaseNode31 = new FibonacciHeapNode<int>(41);

    //     fibDecreaseNode1->right = fibDecreaseNode2;
    //     fibDecreaseNode1->left = fibDecreaseNode3;
    //     fibDecreaseNode1->degree = 3;
    //     fibDecreaseNode1->child = fibDecreaseNode11;
    //     fibDecreaseNode11->parent = fibDecreaseNode1;
    //     fibDecreaseNode11->right = fibDecreaseNode12;
    //     fibDecreaseNode11->left = fibDecreaseNode13;
    //     fibDecreaseNode11->child = fibDecreaseNode111;
    //     fibDecreaseNode11->degree = 2;
    //     fibDecreaseNode111->parent = fibDecreaseNode11;
    //     fibDecreaseNode111->right = fibDecreaseNode112;
    //     fibDecreaseNode111->left = fibDecreaseNode112;
    //     fibDecreaseNode111->isMarked = true;
    //     fibDecreaseNode111->degree = 1;
    //     fibDecreaseNode111->child = fibDecreaseNode1111;
    //     fibDecreaseNode1111->parent = fibDecreaseNode111;
    //     fibDecreaseNode112->parent = fibDecreaseNode11;
    //     fibDecreaseNode112->right = fibDecreaseNode111;
    //     fibDecreaseNode112->left = fibDecreaseNode111;
    //     fibDecreaseNode12->parent = fibDecreaseNode1;
    //     fibDecreaseNode12->right = fibDecreaseNode13;
    //     fibDecreaseNode12->left = fibDecreaseNode11;
    //     fibDecreaseNode12->degree = 1;
    //     fibDecreaseNode12->child = fibDecreaseNode121;
    //     fibDecreaseNode121->parent = fibDecreaseNode12;
    //     fibDecreaseNode13->parent = fibDecreaseNode1;
    //     fibDecreaseNode13->right = fibDecreaseNode11;
    //     fibDecreaseNode13->left = fibDecreaseNode12;
    //     fibDecreaseNode2->right = fibDecreaseNode3;
    //     fibDecreaseNode2->left = fibDecreaseNode1;
    //     fibDecreaseNode2->child = fibDecreaseNode21;
    //     fibDecreaseNode2->degree = 2;
    //     fibDecreaseNode2->isMarked = true;
    //     fibDecreaseNode21->parent = fibDecreaseNode2;
    //     fibDecreaseNode21->right = fibDecreaseNode22;
    //     fibDecreaseNode21->left = fibDecreaseNode22;
    //     fibDecreaseNode21->child = fibDecreaseNode211;
    //     fibDecreaseNode21->degree = 1;
    //     fibDecreaseNode211->parent = fibDecreaseNode21;
    //     fibDecreaseNode22->parent = fibDecreaseNode2;
    //     fibDecreaseNode22->right = fibDecreaseNode21;
    //     fibDecreaseNode22->left = fibDecreaseNode21;
    //     fibDecreaseNode22->isMarked = true;
    //     fibDecreaseNode3->right = fibDecreaseNode1;
    //     fibDecreaseNode3->left = fibDecreaseNode2;
    //     fibDecreaseNode3->child = fibDecreaseNode31;
    //     fibDecreaseNode3->degree = 1;
    //     fibDecreaseNode31->parent = fibDecreaseNode3;

    //     FibonacciHeap<int> decreaseKeyFibHeap(fibDecreaseNode1, 14);
    //     std::cout << "Initial decrease key example state (521p): " << std::endl;
    //     std::cout << decreaseKeyFibHeap << std::endl;
    //     decreaseKeyFibHeap.decreaseKey(fibDecreaseNode112, 15);
    //     std::cout << "Figure 19.5 b): " << std::endl;
    //     std::cout << decreaseKeyFibHeap << std::endl;
    //     decreaseKeyFibHeap.decreaseKey(fibDecreaseNode1111, 5);
    //     std::cout << "Figure 19.5 e): " << std::endl;
    //     std::cout << decreaseKeyFibHeap << std::endl;

    //     decreaseKeyFibHeap.insert(10);
    //     std::cout << "After inserting 10: " << std::endl;
    //     std::cout << decreaseKeyFibHeap << std::endl;

    //     decreaseKeyFibHeap.delete_(fibDecreaseNode13);
    //     std::cout << "After deleting 23: " << std::endl;
    //     std::cout << decreaseKeyFibHeap << std::endl;

    //     std::cout << "Union of the two heaps: " << std::endl;
    //     std::cout << "Target before: " << std::endl
    //               << decreaseKeyFibHeap << std::endl;
    //     std::cout << "Other before: " << std::endl
    //               << extractMinFibHeap << std::endl;

    //     decreaseKeyFibHeap.union_(extractMinFibHeap);
    //     std::cout << "After union: " << std::endl;
    //     std::cout << "Target after: " << std::endl
    //               << decreaseKeyFibHeap << std::endl;
    //     std::cout << "Other after: " << std::endl
    //               << extractMinFibHeap << std::endl;
    // }

    // // MinHeap testing
    // {
    //     MinHeap<int> buildMinHeap({-4, -1, -3, -2, -16, -9, -10, -14, -8, -7});
    //     std::cout << "Build max heapify example state (158p): " << std::endl;
    //     std::cout << buildMinHeap << std::endl;

    //     MinHeap<int> decreaseKeyMinHeap({-16, -14, -10, -8, -7, -9, -3, -2, -4, -1});
    //     std::cout << "Initial state, decrease key example state (165p reversed): " << std::endl;
    //     std::cout << decreaseKeyMinHeap << std::endl;
    //     decreaseKeyMinHeap.decreaseKey(-4, -15);
    //     std::cout << "After key decrease: " << std::endl;
    //     std::cout << decreaseKeyMinHeap << std::endl;

    //     std::cout << "After insert: " << std::endl;
    //     decreaseKeyMinHeap.insert(-12);
    //     std::cout << decreaseKeyMinHeap << std::endl;

    //     auto minVal = decreaseKeyMinHeap.extractMin();
    //     std::cout << "Min value: " << minVal << ", heap: " << std::endl
    //               << decreaseKeyMinHeap << std::endl;
    // }

    return 0;
}
