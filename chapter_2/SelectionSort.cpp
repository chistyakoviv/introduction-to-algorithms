#include <iostream>
#include <vector>

void selectionSort(std::vector<int32_t>& A)
{
    // Loop invariant: A[0..i-1] comprises least values in sorted order
    for (size_t i = 0; i < A.size() - 1; i++)
    {
        for (size_t j = i + 1; j < A.size(); j++)
        {
            if (A[i] > A[j])
            {
                int32_t tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
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

    selectionSort(in);

    std::cout << "\nSorted sequence:\n";
    std::cout << "[ ";
    for (auto v: in)
    {
        std::cout << v << " ";
    }
    std::cout << "]\n\n";
}
