#include "ThreadPool.hpp"

void ThreadPool::work()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(locked);
        avaliable.wait(lock, [&]()
                       { return !running || !tasks.empty(); });

        if (!running)
        {
            break;
        }

        std::function<void()> task = tasks.front().task;

        tasks.pop();
        lock.unlock();

        task();
    }
}

ThreadPool::ThreadPool(int maxThreads) : tasks(), running(true),
                                         locked(), avaliable(),
                                         maxThreads(maxThreads),
                                         threads(new std::thread[maxThreads])
{
    for (int i = 0; i < maxThreads; i++)
    {
        threads[i] = std::thread(&ThreadPool::work, this);
    }
}

ThreadPool::~ThreadPool()
{
    if (running)
    {
        end();
    }
}

void ThreadPool::end()
{
    while (!tasks.empty())
    {
        continue;
    }

    running = false;
    avaliable.notify_all();

    for (int i = 0; i < maxThreads; i++)
    {
        if (threads[i].joinable())
        {
            threads[i].join();
        }
    }

    delete[] threads;
}