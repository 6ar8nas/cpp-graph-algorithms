#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>

template <typename T>
struct FibonacciHeapNode
{
public:
    T key;
    int degree;
    bool isMarked;

    FibonacciHeapNode<T> *child;
    FibonacciHeapNode<T> *left;
    FibonacciHeapNode<T> *right;
    FibonacciHeapNode<T> *parent;

    FibonacciHeapNode(const T &key) : key(key), degree(0), isMarked(false),
                                      child(nullptr), left(this), right(this), parent(nullptr) {}

    ~FibonacciHeapNode()
    {
        if (child == nullptr)
            return;

        FibonacciHeapNode<T> *cur = child;
        do
        {
            FibonacciHeapNode<T> *next = cur->right;
            delete cur;
            cur = next;
        } while (cur != child);
    }

    void print() const { printDeep(0, this); }

private:
    void printDeep(int level, const FibonacciHeapNode<T> *initialNode) const
    {
        for (int i = 0; i < level; ++i)
            std::cout << ">";
        std::cout << key << " (" << degree << ") " << (isMarked ? "marked" : "") << std::endl;

        if (child != nullptr)
            child->printDeep(level + 1, const_cast<FibonacciHeapNode<T> *>(child));

        if (right != initialNode)
            right->printDeep(level, initialNode);
    }
};

template <typename T>
class FibonacciHeap
{
private:
    FibonacciHeapNode<T> *minNode;
    int numNodes;

public:
    FibonacciHeap(FibonacciHeapNode<T> *minNode = nullptr, int numNodes = 0) : minNode(minNode), numNodes(numNodes) {}

    ~FibonacciHeap()
    {
        if (minNode == nullptr)
            return;

        FibonacciHeapNode<T> *cur = minNode;
        do
        {
            FibonacciHeapNode<T> *next = cur->right;
            delete cur;
            cur = next;
        } while (cur != minNode);
    }

    FibonacciHeapNode<T> *insert(const T &key)
    {
        FibonacciHeapNode<T> *newNode = new FibonacciHeapNode<T>(key);
        if (minNode == nullptr)
            minNode = newNode;
        else
        {
            attachToRootList(newNode);
            if (newNode->key < minNode->key)
                minNode = newNode;
        }
        ++numNodes;
        return newNode;
    }

    FibonacciHeapNode<T> *minimum() const { return minNode; }

    FibonacciHeap<T> *union_(FibonacciHeap<T> &other)
    {
        if (other.minNode == nullptr)
            return this;

        if (minNode == nullptr)
            minNode = other.minNode;
        else
        {
            FibonacciHeapNode<T> *lastNode = minNode->left;
            minNode->left = other.minNode->left;
            other.minNode->left->right = minNode;
            other.minNode->left = lastNode;
            lastNode->right = other.minNode;
            if (other.minNode->key < minNode->key)
                minNode = other.minNode;
        }
        numNodes += other.numNodes;
        other.minNode = nullptr;
        other.numNodes = 0;
        return this;
    }

    FibonacciHeapNode<T> *extractMin()
    {
        FibonacciHeapNode<T> *z = minNode;
        if (z == nullptr)
            return z;

        FibonacciHeapNode<T> *child = z->child;
        if (child != nullptr)
        {
            FibonacciHeapNode<T> *x = child;
            do
            {
                FibonacciHeapNode<T> *next = x->right;
                x->parent = nullptr;

                attachToRootList(x);
                x = next;
            } while (x != child);
            z->child = nullptr;
        }

        removeFromRootList(z);
        if (z == z->right)
            minNode = nullptr;
        else
        {
            minNode = z->right;
            consolidate();
        }
        --numNodes;

        z->left = nullptr;
        z->right = nullptr;
        z->degree = 0;
        return z;
    }

    void decreaseKey(FibonacciHeapNode<T> *node, const T &key)
    {
        if (key > node->key)
        {
            std::cerr << "New key is greater than current key" << std::endl;
            return;
        }

        node->key = key;
        FibonacciHeapNode<T> *parent = node->parent;
        if (parent != nullptr && node->key < parent->key)
        {
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->key < minNode->key)
            minNode = node;
    }

    void delete_(FibonacciHeapNode<T> *node)
    {
        decreaseKey(node, std::numeric_limits<T>::min());
        extractMin();
    }

    void printHeap()
    {
        if (minNode != nullptr)
            minNode->print();
        else
            std::cout << "<BLANK>" << std::endl;
    }

private:
    void consolidate()
    {
        int maxDegree = static_cast<int>(log(numNodes) / log((1 + sqrt(5)) / 2)) + 1;
        std::vector<FibonacciHeapNode<T> *> A(maxDegree, nullptr);
        FibonacciHeapNode<T> *x = minNode;
        do
        {
            int d = x->degree;
            while (A[d] != nullptr)
            {
                FibonacciHeapNode<T> *y = A[d];
                if (x->key > y->key)
                    std::swap(x, y);
                link(y, x);
                A[d] = nullptr;
                ++d;
            }
            A[d] = x;
            x = x->right;
        } while (x != minNode);

        minNode = nullptr;

        for (int i = 0; i < maxDegree; ++i)
        {
            if (A[i] == nullptr)
                continue;

            if (minNode == nullptr)
            {
                minNode = A[i];
                minNode->left = minNode;
                minNode->right = minNode;
            }
            else
            {
                attachToRootList(A[i]);
                if (A[i]->key < minNode->key)
                    minNode = A[i];
            }
        }
    }

    void link(FibonacciHeapNode<T> *highNode, FibonacciHeapNode<T> *lowNode)
    {
        removeFromRootList(highNode);

        highNode->parent = lowNode;
        if (lowNode->child == nullptr)
        {
            lowNode->child = highNode;
            highNode->left = highNode;
            highNode->right = highNode;
        }
        else
        {
            highNode->left = lowNode->child->left;
            highNode->right = lowNode->child;
            lowNode->child->left = highNode;
            highNode->left->right = highNode;
            lowNode->child = highNode;
        }
        ++lowNode->degree;
        highNode->isMarked = false;
    }

    void cut(FibonacciHeapNode<T> *node, FibonacciHeapNode<T> *parent)
    {
        if (node == node->right)
            parent->child = nullptr;
        else
        {
            node->left->right = node->right;
            node->right->left = node->left;
            if (parent->child == node)
                parent->child = node->right;
        }
        parent->degree--;

        attachToRootList(node);

        node->parent = nullptr;
        node->isMarked = false;
    }

    void cascadingCut(FibonacciHeapNode<T> *node)
    {
        FibonacciHeapNode<T> *z = node->parent;
        if (z == nullptr)
            return;

        if (!node->isMarked)
            node->isMarked = true;
        else
        {
            cut(node, z);
            cascadingCut(z);
        }
    }

    void attachToRootList(FibonacciHeapNode<T> *node)
    {
        minNode->left->right = node;
        node->right = minNode;
        node->left = minNode->left;
        minNode->left = node;
    }

    void removeFromRootList(FibonacciHeapNode<T> *node)
    {
        if (node == node->right)
            minNode = nullptr;
        else if (node == minNode)
            minNode = minNode->right;

        node->left->right = node->right;
        node->right->left = node->left;
    }
};

#endif
