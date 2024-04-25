#include <vector>
#include <random>
#include <iostream>
#include <omp.h>
#include <iomanip>

#include "constants.h"

size_t N = 0;

void initMatrixRandom(Matrix &matrix)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1000.0);

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            matrix[i][j] = dist(mt);
        }
    }
}

Matrix matrixMultiplication(const Matrix &A, const Matrix &B, int K)
{
    Matrix C(N, std::vector<double>(N));

    #pragma omp parallel for
    for (size_t i = 0; i < N; ++i)
    {
        #pragma omp parallel for
        for (size_t j = 0; j < N; ++j)
        {
            double &elem = C[i][j];
            
            #pragma omp parallel for reduction(+:elem)
            for (size_t k = 0; k < N; ++k)
            {
                elem += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

void run(size_t matrixSize)
{
    N = matrixSize;

    Matrix A(N, std::vector<double>(N));
    Matrix B(N, std::vector<double>(N));

    initMatrixRandom(A);
    initMatrixRandom(B);

    for (int K = 1; K <= 2 * p; ++K)
    {
        omp_set_num_threads(K);
        auto start_time = omp_get_wtime();
        matrixMultiplication(A, B, K);
        auto end_time = omp_get_wtime();

        std::cout << std::setw(20) << std::left << K << std::setw(20) << std::left << N << std::setw(20) << std::left << (end_time - start_time) * 1000 << "\n";
    }
}

int main()
{
    run(10);
    run(100);
    run(1000);

    return 0;
}