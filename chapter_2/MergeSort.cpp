#include <iostream>
#include <vector>

void merge(std::vector<int32_t>& A, size_t p, size_t q, size_t r)
{
    size_t n1 = q - p + 1;
    size_t n2 = r - q;

    // We won't be using sentinels, so we don't need extra space
    int32_t L[n1], R[n2];
    for (size_t i = 0; i < n1; i++)
        L[i] = A[p + i];

    for (size_t i = 0; i < n2; i++)
        R[i] = A[q + i + 1];

    size_t i = 0, j = 0, k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    // Copy the rest back to A
    while (i < n1)
        A[k++] = L[i++];

    while (j < n2)
        A[k++] = R[j++];
}

void mergeSort(std::vector<int32_t>& A, size_t p, size_t r)
{
    if (p < r)
    {
        size_t q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
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

    mergeSort(in, 0, in.size() - 1);

    std::cout << "\nSorted sequence:\n";
    std::cout << "[ ";
    for (auto v: in)
    {
        std::cout << v << " ";
    }
    std::cout << "]\n\n";
}
