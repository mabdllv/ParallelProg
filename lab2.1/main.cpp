#include <iostream>
#include <mpi.h>
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

    double startTime, endTime;
    startTime = MPI_Wtime();
    
    for (int K = 1; K <= 2 * p; ++K)
    {
        for (int i = 0; i < N; ++i)
        {
            totalIntegral += (( f(a + unit * i) + f(a + (unit * (i + 1))) ) / 2) * unit;
        }

        endTime = MPI_Wtime();

        std::cout << std::setw(4) << std::left << K << std::setw(8) << std::left << N << std::setw(11) << std::left << totalIntegral << std::setw(11) << std::left << endTime - startTime << "\n";

        totalIntegral = 0;
    }

}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int N = 10;

    while (N <= 100000)
    {
        run(N);
        N *= 10;
    }

    MPI_Finalize();

    return 0;
}