#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "../utils/assert.h"

static const int32_t MINUS_INF = 0x80000000;

class Heap
{
public:
    Heap(const std::vector<int32_t>& elements)
        : m_Elements(elements)
    {}

    const int32_t& operator[](size_t index) const
    {
        return m_Elements[index];
    }

    size_t size() const
    {
        return m_Elements.size();
    }

    size_t parent(size_t i) const
    {
        return (i + 1) / 2 - 1;
    }

    size_t left(size_t i) const
    {
        return 2 * (i + 1) - 1;
    }

    size_t right(size_t i) const
    {
        return 2 * (i + 1);
    }

    friend std::ostream& operator<<(std::ostream& os, const Heap& heap);
protected:
    void exchange(size_t i, size_t j)
    {
        int32_t tmp = m_Elements[i];
        m_Elements[i] = m_Elements[j];
        m_Elements[j] = tmp;
    }
protected:
    std::vector<int32_t> m_Elements;
};

std::ostream& operator<<(std::ostream& os, const Heap& heap)
{
    // The size of the last level is 2^lg(heap.size()).
    // To add space between neighbor elements we
    // double the size and add one.
    size_t lastLevelSize = pow(2, floor(log2(heap.size()))) * 2 + 1;
    size_t currentLevel = 0;

    for (size_t i = 0; i < heap.size(); i++)
    {
        size_t level = floor(log2(i + 1));
        size_t offset = lastLevelSize / (pow(2, level) + 1);

        if (level != currentLevel)
        {
            currentLevel = level;
            os << "\n";
        }

        os << std::string(offset, ' ') << heap[i];
    }

    return os;
}

class MaxPriorityQueue : public Heap
{
public:
    MaxPriorityQueue(std::vector<int32_t> elements)
        : Heap(elements)
    {
        buildMaxHeap();
    }

    int32_t maximum()
    {
        return m_Elements[0];
    }

    int32_t extract()
    {
        ASSERT(size() > 0, "heap underflow");

        int32_t max = m_Elements[0];
        m_Elements[0] = m_Elements[size() - 1];
        m_Elements.pop_back();
        maxHeapify(0);

        return max;
    }

    void increaseKey(size_t i, int32_t key)
    {
        ASSERT(key >= m_Elements[i], "new key is smaller than current key");

        m_Elements[i] = key;
        while (i > 0 && key > m_Elements[parent(i)])
        {
            exchange(i, parent(i));
            i = parent(i);
        }
    }

    void insert(int32_t key)
    {
        m_Elements.push_back(MINUS_INF);
        increaseKey(size() - 1, key);
    }
private:
    void buildMaxHeap()
    {
        for (size_t i = size() / 2; i > 0; i--)
            maxHeapify(i - 1);
    }

    void maxHeapify(size_t i)
    {
        size_t l = left(i);
        size_t r = right(i);

        size_t largest = i;

        if (l < size() && m_Elements[l] > m_Elements[largest])
            largest = l;

        if (r < size() && m_Elements[r] > m_Elements[largest])
            largest = r;

        if (largest != i)
        {
            exchange(i, largest);
            maxHeapify(largest);
        }
    }
};

int main()
{
    MaxPriorityQueue queue({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});
    std::cout << queue << std::endl;

    ASSERT(queue.size() == 10, "wrong queue size");

    int32_t max = queue.extract();
    ASSERT(max == 16, "wrong extracted maximum element");
    ASSERT(queue.size() == 9, "wrong queue size");

    queue.insert(20);
    max = queue.maximum();
    ASSERT(max == 20, "wrong maximum element");
    ASSERT(queue.size() == 10, "wrong queue size");

    std::cout << queue << std::endl;
}
