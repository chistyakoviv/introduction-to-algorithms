#include <iostream>
#include <vector>

static const int32_t MINUS_INFINITY = 0x80000000; // Min int32_t value

struct SubarrayData
{
    int32_t sum = 0;
    size_t low = 0;
    size_t high = 0;
};

SubarrayData FindMaxCrossingSubarray(std::vector<int32_t>& A, size_t low, size_t mid, size_t high)
{
    int32_t sum = 0;
    int32_t left_sum = MINUS_INFINITY;
    size_t max_left = 0;
    // In order to use unsigned counter
    // we shift the counter to the right in the init statement
    // and back to the left in the body of the loop.
    for (size_t i = mid + 1; i > low; i--)
    {
        sum += A[i - 1];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i - 1;
        }
    }

    sum = 0;
    int32_t right_sum = MINUS_INFINITY;
    size_t max_right = mid + 1;
    for (size_t j = mid + 1; j < high + 1; j++)
    {
        sum += A[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }

    return { left_sum + right_sum, max_left, max_right };
}

SubarrayData FindMaximumSubarray(std::vector<int32_t>& A, size_t low, size_t high)
{
    if (low == high)
        return { A[low], low, high };

    size_t mid = (low + high) / 2;
    SubarrayData left = FindMaximumSubarray(A, low, mid);
    SubarrayData right = FindMaximumSubarray(A, mid + 1, high);
    SubarrayData cross = FindMaxCrossingSubarray(A, low, mid, high);

    if (left.sum > right.sum && left.sum > cross.sum)
        return left;

    if (right.sum > left.sum && right.sum > cross.sum)
        return right;

    return cross;
}

int main()
{
    std::vector<int32_t> in = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };

    SubarrayData result = FindMaximumSubarray(in, 0, in.size() - 1);
    std::cout << "low: " << result.low << " high: " << result.high << " sum: " << result.sum << std::endl;
}
