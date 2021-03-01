#include <iostream>
#include <vector>
#include <string>

class SquareMatrix
{
public:
    SquareMatrix() = default;

    SquareMatrix(size_t size)
    {
        m_Elements.resize(size);

        // Create identity matrix.
        for (size_t i = 0; i < size; i++)
        {
            m_Elements[i].resize(size, 0);
            m_Elements[i][i] = 1;
        }
    }

    SquareMatrix(const SquareMatrix& other)
    {
        m_Elements.resize(other.size());

        for (size_t i = 0; i < size(); i++) {
            m_Elements[i].resize(size());

            for (size_t j = 0; j < size(); j++) {
                m_Elements[i][j] = other[i][j];
            }
        }
    }

    std::vector<int32_t>& operator[](size_t index)
    {
        return m_Elements[index];
    }

    const std::vector<int32_t>& operator[](size_t index) const
    {
        return m_Elements[index];
    }

    SquareMatrix operator*(const SquareMatrix& other)
    {
        if (size() != other.size())
            return *this;

        return SquareMatrixMultiplicationRecursive(*this, other);
    }

    SquareMatrix operator+(const SquareMatrix& other)
    {
        if (size() != other.size())
            return *this;

        SquareMatrix result(size());

        for (size_t i = 0; i < size(); i++)
        {
            for (size_t j = 0; j < size(); j++)
            {
                result[i][j] = m_Elements[i][j] + other[i][j];
            }
        }

        return result;
    }

    size_t size() const
    {
        return m_Elements.size();
    }

    std::vector<std::vector<int32_t>>::iterator begin()
    {
        return m_Elements.begin();
    }

    std::vector<std::vector<int32_t>>::iterator end()
    {
        return m_Elements.end();
    }

    static SquareMatrix createPartition(const SquareMatrix& matrix, size_t startRow, size_t endRow, size_t startColumn, size_t endColumn)
    {
        size_t rows = endRow - startRow + 1;
        size_t cols = endColumn - startColumn + 1;
        size_t size = std::min(rows, cols);
        SquareMatrix partition(size);

        size_t row = 0, col = 0;
        for (size_t i = startRow; i < startRow + size; i++)
        {
            col = 0;
            for (size_t j = startColumn; j < startColumn + size; j++)
            {
                partition[row][col++] = matrix[i][j];
            }
            row++;
        }

        return partition;
    }

    static SquareMatrix createFromPartitions(const std::vector<SquareMatrix>& partitions)
    {
        size_t size = 0xFFFF;

        for (auto partition: partitions)
        {
            size = std::min(size, partition.size());
        }

        SquareMatrix result(size * 2);

        for (size_t i = 0; i < partitions.size(); i++)
        {
            size_t row = 0, col = 0;
            // For partitions 0, 1 we fill the rows of the resulting matrix from 0 to size - 1
            // and for partitions 2, 3 we fill the rows of the resulting matrix from size to size * 2 - 1.
            for (size_t j = (size_t)(0.5f * i) % 2 * size; j < ((size_t)(0.5f * i) % 2 + 1) * size; j++)
            {
                col = 0;
                // For partitions 0, 2 we fill the columns of the resulting matrix from 0 to size - 1
                // and for partitions 1, 3 we fill the columns of the resulting matrix from size to size * 2 - 1.
                for (size_t k = i % 2 * size; k < (i % 2 + 1) * size; k++)
                {
                    result[j][k] = partitions[i][row][col++];
                }
                row++;
            }
        }

        return result;
    }

    friend SquareMatrix SquareMatrixMultiplicationRecursive(const SquareMatrix& A, const SquareMatrix& B);
private:
    std::vector<std::vector<int32_t>> m_Elements;
};

void printMatrix(SquareMatrix& matrix)
{
    for (auto row: matrix)
    {
        for (auto col: row)
        {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void fillMatrix(SquareMatrix& matrix, const std::string& name)
{
    int32_t value;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix.size(); j++)
        {
            std::cout << "Input the value of " << name << "[" << i << "]" << "[" << j << "]: ";
            std::cin >> value;
            matrix[i][j] = value;
        }
    }
    std::cout << "\n";
}

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
