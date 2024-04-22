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

    friend std::ostream &operator<<(std::ostream &os, const FibonacciHeapNode<T> &obj)
    {
        os << obj.key << " (" << obj.degree << ") " << (obj.isMarked ? "marked" : "");
        return os;
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

    T extractMin()
    {
        FibonacciHeapNode<T> *z = minNode;
        if (z == nullptr)
            throw std::out_of_range("Heap is empty");

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

        if (minNode != nullptr)
            consolidate();
        --numNodes;

        T key = z->key;
        delete z;
        return key;
    }

    void decreaseKey(FibonacciHeapNode<T> *node, const T &key)
    {
        if (key > node->key)
            throw std::invalid_argument("New key is greater than current key");

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

    bool isEmpty() const { return numNodes == 0; }

    friend std::ostream &operator<<(std::ostream &os, const FibonacciHeap<T> &obj)
    {
        if (!obj.isEmpty())
            obj.printDeep(os, 0, obj.minNode, obj.minNode);
        else
            os << "<BLANK>" << std::endl;
        return os;
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
        if (node == minNode)
        {
            minNode = minNode->right;
            if (node == minNode)
                minNode = nullptr;
        }

        node->left->right = node->right;
        node->right->left = node->left;
    }

    void printDeep(std::ostream &os, int depth, const FibonacciHeapNode<T> *node, const FibonacciHeapNode<T> *initialNode) const
    {
        for (int i = 0; i < depth; ++i)
            os << ">";
        if (depth > 0)
            os << " ";

        os << *node << std::endl;

        if (node->child != nullptr)
            printDeep(os, depth + 1, node->child, node->child);

        if (node->right != initialNode)
            printDeep(os, depth, node->right, initialNode);
    }
};

#endif
