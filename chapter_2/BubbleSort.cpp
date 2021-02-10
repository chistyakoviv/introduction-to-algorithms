#include <iostream>
#include <vector>

void bubbleSort(std::vector<int32_t>& A)
{
    for (size_t i = 0; i < A.size() - 1; i++)
    {
        for (size_t j = A.size() - 1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                uint32_t tmp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tmp;
            }
        }
    }
}

int main()
{
    std::vector<int32_t> in;
    int32_t value;

    std::cout << "Input your numbers (0 terminates the input procedure): ";

    do
    {
        std::cin >> value;
        in.push_back(value);
    } while (value != 0);

    bubbleSort(in);

    std::cout << "\nSorted sequence:\n";
    std::cout << "[ ";
    for (auto v: in)
    {
        std::cout << v << " ";
    }
    std::cout << "]\n\n";
}
