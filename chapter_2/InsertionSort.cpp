#include <iostream>
#include <vector>

void insertionSort(std::vector<int32_t>& A)
{
    for (size_t j = 1; j < A.size(); j++)
    {
        int32_t key = A[j];
        int32_t i = j - 1;

        while (i > -1 && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }

        A[i + 1] = key;
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

    insertionSort(in);

    std::cout << "\nSorted sequence:\n";
    std::cout << "[ ";
    for (auto v: in)
    {
        std::cout << v << " ";
    }
    std::cout << "]\n\n";
}
