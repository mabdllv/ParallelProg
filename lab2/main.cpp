#include <iostream>
#include <omp.h>
#include <math.h>
#include <iomanip>

#include "constants.h"

double f(double x)
{
    return sin(log(x));
}

void run(int N)
{
    double totalIntegral = 0;
    const double unit = static_cast<double>((b - a)) / N;
    
    for (int K = 1; K <= 2 * p; ++K)
    {
        auto start_time = omp_get_wtime();

        omp_set_num_threads(K);
        #pragma omp parallel for reduction(+:totalIntegral)
        for (int i = 0; i < N; ++i)
        {
            totalIntegral += (( f(a + unit * i) + f(a + (unit * (i + 1))) ) / 2) * unit;
        }

        auto end_time = omp_get_wtime();

        std::cout << std::setw(4) << std::left << K << std::setw(8) << std::left << N << std::setw(11) << std::left << totalIntegral << std::setw(10) << std::left << (end_time - start_time) * 1000 << "\n";

        totalIntegral = 0;
    }

}

int main()
{
    int N = 10;

    while (N <= 100000)
    {
        run(N);
        N *= 10;
    }

    return 0;
}