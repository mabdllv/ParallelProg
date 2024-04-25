#include <iostream>
#include <omp.h>

#if defined(_linux__) || defined(__APPLE__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

int readNumberOfThreads()
{
    int K;
    std::cout << "Enter the number of threads: ";
    std::cin >> K;
    return K;
}

int main()
{
    const int K = readNumberOfThreads();
   
    #pragma omp parallel num_threads(K)
    {
        std::string message = "Hello! I'm thread " + std::to_string(omp_get_thread_num() + 1) + " from " + std::to_string(K) + " threads.\n";
        std::cout << message;
    }

    sleep(5);

    #pragma omp parallel num_threads(K)
    {
        int threadNumber = omp_get_thread_num() + 1;
        if (threadNumber % 2 == 0)
        {
            std::string message = "Hello again! I'm thread " + std::to_string(threadNumber) + ". I'm even.\n";
            std::cout << message;
        }
    }
}