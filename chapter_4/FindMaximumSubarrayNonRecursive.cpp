#include <iostream>
#include <vector>

static const int32_t MINUS_INFINITY = 0x80000000; // Min int32_t value

struct SubarrayData
{
    int32_t sum = 0;
    size_t low = 0;
    size_t high = 0;
};

SubarrayData FindMaximumSubarray(std::vector<int32_t>& A)
{
    SubarrayData max = { sum: MINUS_INFINITY };
    SubarrayData current = {};

    for (size_t i = 0; i < A.size(); i++)
    {
        // We need to begin a new current subarray
        // if the sum of the current subarray
        // makes the next element smaller.
        if (current.sum + A[i] < A[i])
        {
            current.sum = 0;
            current.low = i;
        }

        current.sum += A[i];
        current.high = i;

        if (current.sum > max.sum)
        {
            max.sum = current.sum;
            max.low = current.low;
            max.high = current.high;
        }
    }

    return max;
}

int main()
{
    std::vector<int32_t> in = { 13, -3, -25, 20, -3, -16, -23, 18, 20, 40, 80, -7, 12, -5, 10, -22, 15, -4, 7 };

    SubarrayData result = FindMaximumSubarray(in);
    std::cout << "low: " << result.low << " high: " << result.high << " sum: " << result.sum << std::endl;
}
