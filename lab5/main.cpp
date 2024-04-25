#include <iostream>
#include <omp.h>
#include <math.h>
#include <iomanip>
#include <vector>

constexpr unsigned p = 12;

bool hasNoDividers(unsigned value, unsigned K)
{
    for (unsigned divider = 2; divider <= static_cast<unsigned>(sqrt(value)); ++divider)
    {
        if (value % divider == 0)
            return false;
    }

    return true;
}

void getPrimes(unsigned M, unsigned N)
{
    std::vector<unsigned> primes;

    for (unsigned K = 1; K <= 2 * p; ++K)
    {
        primes.clear();

        auto start_time = omp_get_wtime();

        omp_set_num_threads(K);
        #pragma omp parallel for
        for (unsigned value = M; value <= N; ++value)
        {
            if (hasNoDividers(value, K))
                primes.push_back(value);
        }

        auto end_time = omp_get_wtime();

        std::cout << std::setw(4) << std::left << K << (end_time - start_time) * 1000 << "\n";
    }
}

int main()
{
    getPrimes(10000, 100000);

    return 0;
}