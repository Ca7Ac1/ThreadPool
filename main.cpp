#include <iostream>
#include <chrono>

#include "ThreadPool.hpp"

void add(int a, int b)
{
    int c = a + b;
}

void smallChunk()
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < (int)1e6; i++)
    {
        add(i, i % 700 * 7);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Running on main thread: " << duration.count() << " milliseconds" << std::endl;

    for (int threadCount = 1; threadCount <= 10; threadCount++)
    {
        ThreadPool pool(threadCount);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < (int)1e6; i++)
        {
            pool.addTask(&add, i, i % 700 * 7);
        }

        pool.end();

        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Running on " << threadCount << " thread: " << duration.count() << " milliseconds" << std::endl;
    }
}

void addMany(int a, int b)
{
    for (int i = 0; i < (int)1e6; i++)
    {
        int c = a + b;
    }
}

void bigChunk()
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < (int)1e3; i++)
    {
        addMany(i, i % 700 * 7);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Running on main thread: " << duration.count() << " milliseconds" << std::endl;

    for (int threadCount = 1; threadCount <= 10; threadCount++)
    {
        ThreadPool pool(threadCount);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < (int)1e3; i++)
        {
            pool.addTask(&addMany, i, i % 700 * 7);
        }

        pool.end();

        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Running on " << threadCount << " thread: " << duration.count() << " milliseconds" << std::endl;
    }
}

int main()
{
    std::cout << "SMALL CHUNKS: 1e6 additions each on a different thread" << std::endl;
    std::cout << "______________________________________________________" << std::endl;
    smallChunk();
   
    std::cout << "BIG CHUNKS: 1e3 additions of chunks of 1e6 size" << std::endl;
    std::cout << "_______________________________________________" << std::endl;
    bigChunk();

    return 0;
}