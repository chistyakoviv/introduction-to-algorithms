#include "Matrix.h"

// Strassen's algorithm
SquareMatrix SquareMatrixMultiplication(const SquareMatrix& A, const SquareMatrix& B)
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

    SquareMatrix S1 = B12 - B22;
    SquareMatrix S2 = A11 + A12;
    SquareMatrix S3 = A21 + A22;
    SquareMatrix S4 = B21 - B11;
    SquareMatrix S5 = A11 + A22;
    SquareMatrix S6 = B11 + B22;
    SquareMatrix S7 = A12 - A22;
    SquareMatrix S8 = B21 + B22;
    SquareMatrix S9 = A11 - A21;
    SquareMatrix S10 = B11 + B12;

    SquareMatrix P1 = A11 * S1;
    SquareMatrix P2 = S2 * B22;
    SquareMatrix P3 = S3 * B11;
    SquareMatrix P4 = A22 * S4;
    SquareMatrix P5 = S5 * S6;
    SquareMatrix P6 = S7 * S8;
    SquareMatrix P7 = S9 * S10;

    SquareMatrix C11 = P5 + P4 - P2 + P6;
    SquareMatrix C12 = P1 + P2;
    SquareMatrix C21 = P3 + P4;
    SquareMatrix C22 = P5 + P1 - P3 - P7;

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
