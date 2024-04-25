#include <iostream>
#include <omp.h>
#include <math.h>
#include <iomanip>

constexpr unsigned p = 12;

void calculatePi(int N)
{
    long double pi = 1;

    for (unsigned K = 1; K <= 2 * p; ++K)
    {
        auto start_time = omp_get_wtime();

        omp_set_num_threads(K);
        #pragma omp parallel for reduction(*:pi)
        for (int n = 1; n <= N; ++n)
        {
            double x = 4 * n * n;
            pi *= (x) / (x -1);
        }

        pi *= 2;

        auto end_time = omp_get_wtime();

        std::cout << std::setw(4) << std::left << K << std::setw(8) << std::left << N << std::setw(10) << std::left << pi << std::setw(4) << std::left << (end_time - start_time) * 1000 << "\n";

        pi = 1;
    }
}

int parallelExp(int base, unsigned exp, unsigned K)
{
    unsigned x = 1;

    omp_set_num_threads(K);
    #pragma omp parallel for reduction(*:x)
    for (unsigned i = 1; i <= exp; ++i)
    {
        x *= base;
    }

    return x;
}

void calculateE(int N)
{
    long double e = 1;

    for (unsigned K = 1; K <= 2 * p; ++K)
    {
        double base = 1 + (1.0 / N);

        auto start_time = omp_get_wtime();

        omp_set_num_threads(K);
        #pragma omp parallel for reduction(*:e)
        for (int n = 1; n <= N; ++n)
        {
            e *= base;
        }

        auto end_time = omp_get_wtime();

        std::cout << std::setw(4) << std::left << K << std::setw(8) << std::left << N << std::setw(14) << std::left << e << std::setw(4) << std::left << (end_time - start_time) * 1000 << "\n";

        e = 1;
    }
}

void testCalculation(void (*func)(int))
{
    int N = 10;

    while (N <= 100000)
    {
        func(N);
        N *= 10;
    }
}

int main()
{
    std::cout << "Test pi calculating\n";
    testCalculation(calculatePi);
    std::cout << "Test e calculating\n";
    testCalculation(calculateE);

    return 0;
}