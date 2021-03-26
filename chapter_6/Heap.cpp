#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Heap
{
public:
    Heap(const std::vector<int32_t>& elements)
        : m_Elements(elements), m_HeapSize(elements.size())
    {}

    const int32_t& operator[](size_t index) const
    {
        return m_Elements[index];
    }

    size_t length() const
    {
        return m_Elements.size();
    }

    size_t heapSize() const
    {
        return m_HeapSize;
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
    size_t m_HeapSize;
};

std::ostream& operator<<(std::ostream& os, const Heap& heap)
{
    // The size of the last level is 2^lg(heap.length()).
    // To add space between neighbor elements we
    // double the size and add one.
    size_t lastLevelSize = pow(2, floor(log2(heap.length()))) * 2 + 1;
    size_t currentLevel = 0;

    for (size_t i = 0; i < heap.length(); i++)
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

class MaxHeap : public Heap
{
public:
    MaxHeap(std::vector<int32_t> elements)
        : Heap(elements)
    {
        buildMaxHeap();
    }
private:
    void buildMaxHeap()
    {
        for (size_t i = length() / 2; i > 0; i--)
            maxHeapify(i - 1);
    }

    void maxHeapify(size_t i)
    {
        size_t l = left(i);
        size_t r = right(i);

        size_t largest = i;

        if (l < heapSize() && m_Elements[l] > m_Elements[largest])
            largest = l;

        if (r < heapSize() && m_Elements[r] > m_Elements[largest])
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
    MaxHeap heap({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});
    std::cout << heap << std::endl;
}
