#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

struct Task
{
    std::function<void()> task;
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

    template <typename Callable, typename... Args>
    void addTask(Callable &&f, Args &&...args)
    {
        std::unique_lock<std::mutex> lock(locked);

        Task task;
        task.task = std::bind(f, args...);

        tasks.push(task);

        lock.unlock();
        avaliable.notify_one();
    }

    void end();
};

#endif