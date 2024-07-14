#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

template <typename T, typename THash = std::hash<T>, typename TEquals = std::equal_to<T>>
class MinHeap
{
private:
    std::vector<T> heap;
    int size;
    std::unordered_map<T, int, THash, TEquals> keyHeapIndexMap;

public:
    MinHeap(std::vector<T> elements = {}) : heap(elements), size(elements.size())
    {
        int index = 1;
        for (auto const &elem : elements)
            keyHeapIndexMap[elem] = index++;

        for (int i = size / 2; i >= 1; --i)
            heapify(i);
    }

    void insert(const T &key)
    {
        heap.push_back(key);
        keyHeapIndexMap[key] = ++size;
        decreaseKey(key, key);
    }

    T minimum() const { return heap.front(); }

    T extractMin()
    {
        if (size < 1)
            throw std::out_of_range("Heap is empty");

        T min = heap.front();
        std::swap(heap[0], heap[size - 1]);
        std::swap(keyHeapIndexMap[heap[0]], keyHeapIndexMap[heap[size - 1]]);
        heap.pop_back();
        --size;
        heapify(1);
        return min;
    }

    void decreaseKey(const T &elemIdentifier, const T &newKey)
    {
        int elemIndex = keyHeapIndexMap[elemIdentifier];
        if (newKey > heap[elemIndex - 1])
            throw std::invalid_argument("New key is greater than current key");

        heap[elemIndex - 1] = newKey;
        while (elemIndex > 1 && heap[parent(elemIndex) - 1] > heap[elemIndex - 1])
        {
            std::swap(heap[elemIndex - 1], heap[parent(elemIndex) - 1]);
            std::swap(keyHeapIndexMap[heap[elemIndex - 1]], keyHeapIndexMap[heap[parent(elemIndex) - 1]]);
            elemIndex = parent(elemIndex);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const MinHeap<T, THash, TEquals> &obj)
    {
        if (!obj.isEmpty())
            obj.printDeep(os, 1, 0);
        else
            os << "<BLANK>" << std::endl;
        return os;
    }

    bool isEmpty() const { return size == 0; }

private:
    void heapify(int elemIndex)
    {
        int l = left(elemIndex);
        int r = right(elemIndex);
        int smallest;

        if (l <= size && heap[l - 1] < heap[elemIndex - 1])
            smallest = l;
        else
            smallest = elemIndex;

        if (r <= size && heap[r - 1] < heap[smallest - 1])
            smallest = r;

        if (smallest != elemIndex)
        {
            std::swap(heap[elemIndex - 1], heap[smallest - 1]);
            std::swap(keyHeapIndexMap[heap[elemIndex - 1]], keyHeapIndexMap[heap[smallest - 1]]);
            heapify(smallest);
        }
    }

    int parent(int elemIndex) const { return elemIndex / 2; }

    int left(int elemIndex) const { return 2 * elemIndex; }

    int right(int elemIndex) const { return 2 * elemIndex + 1; }

    void printDeep(std::ostream &os, int elemIndex, int depth) const
    {
        if (elemIndex > size)
            return;

        for (int i = 0; i < depth; ++i)
            os << ">";
        if (depth > 0)
            os << " ";

        os << heap[elemIndex - 1] << std::endl;

        printDeep(os, left(elemIndex), depth + 1);
        printDeep(os, right(elemIndex), depth + 1);
    }
};

#endif // MIN_HEAP_H