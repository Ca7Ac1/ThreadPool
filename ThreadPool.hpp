#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <queue>
#include <functional>
#include <thread>
#include <mutex>

struct Task 
{
    std::function<void()> &task;
};

class ThreadPool
{
private:
    std::queue<Task> tasks;
    std::thread *threads;

    std::mutex locked;
    std::condition_variable avaliable;

    int maxThreads;
    bool running;

    void work();

public:
    ThreadPool(int maxThreads);
    ~ThreadPool();

    template <class... Args>
    void addTask(std::function<void()> f, Args... args);

    void join();
};

#endif