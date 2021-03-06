#include "Matrix.h"

SquareMatrix SquareMatrixMultiplicationRecursive(const SquareMatrix& A, const SquareMatrix& B)
{
    size_t n = std::min(A.size(), B.size());

    SquareMatrix C(n);

    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    size_t middle = (n - 1) / 2;

    SquareMatrix A11 = SquareMatrix::createPartition(A, 0, middle, 0, middle);
    SquareMatrix A12 = SquareMatrix::createPartition(A, 0, middle, middle + 1, n - 1);
    SquareMatrix A21 = SquareMatrix::createPartition(A, middle + 1, n - 1, 0, middle);
    SquareMatrix A22 = SquareMatrix::createPartition(A, middle + 1, n - 1, middle + 1, n - 1);
    SquareMatrix B11 = SquareMatrix::createPartition(B, 0, middle, 0, middle);
    SquareMatrix B12 = SquareMatrix::createPartition(B, 0, middle, middle + 1, n - 1);
    SquareMatrix B21 = SquareMatrix::createPartition(B, middle + 1, n - 1, 0, middle);
    SquareMatrix B22 = SquareMatrix::createPartition(B, middle + 1, n - 1, middle + 1, n - 1);

    SquareMatrix C11 = SquareMatrixMultiplicationRecursive(A11, B11)
                     + SquareMatrixMultiplicationRecursive(A12, B21);
    SquareMatrix C12 = SquareMatrixMultiplicationRecursive(A11, B12)
                     + SquareMatrixMultiplicationRecursive(A12, B22);
    SquareMatrix C21 = SquareMatrixMultiplicationRecursive(A21, B11)
                     + SquareMatrixMultiplicationRecursive(A22, B21);
    SquareMatrix C22 = SquareMatrixMultiplicationRecursive(A21, B12)
                     + SquareMatrixMultiplicationRecursive(A22, B22);

    std::vector<SquareMatrix> partitions;
    partitions.push_back(C11);
    partitions.push_back(C12);
    partitions.push_back(C21);
    partitions.push_back(C22);

    C = SquareMatrix::createFromPartitions(partitions);

    return C;
}

int main()
{
    size_t size = 0;

    std::cout << "Input matrices size: ";
    std::cin >> size;
    std::cout << "\n";

    SquareMatrix A(size), B(size);

    fillMatrix(A, "A");
    fillMatrix(B, "B");

    SquareMatrix C = A * B;

    std::cout << "Result:\n";
    printMatrix(C);
}
