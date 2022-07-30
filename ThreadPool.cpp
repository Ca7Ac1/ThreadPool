#include <ThreadPool.hpp>

void ThreadPool::work()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock(locked);
        avaliable.wait(lock, [&]()
                       { return !running || !tasks.empty(); });

        std::function<void()> task = tasks.front();

        tasks.pop();
        lock.unlock();

        task();
    }
}

ThreadPool::ThreadPool(int maxThreads) : running(true), threads(new std::thread[maxThreads])
{
    for (int i = 0; i < maxThreads; i++)
    {
        threads[i] = std::thread(&work);
    }
}

ThreadPool::~ThreadPool()
{
    delete[] threads;
    running = false;
}

template <class... Args>
void ThreadPool::addTask(std::function<void()> f, Args... args)
{
    std::unique_lock<std::mutex> lock(locked);

    tasks.push(std::bind(f, args));

    lock.unlock();
    avaliable.notify_one();
}