#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <future>
#include <queue>
#include <mutex>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(const size_t poolSize)
      : stopFlag(false) {

        for (size_t i = 0; i < poolSize; ++i) {
            threadVector.emplace_back([this] {
                for (;;) {
                    std::function<void()> curTask;
                    std::unique_lock<std::mutex> lock(mutexThread);
                    conditionVar.wait(lock, [this] {return stopFlag || !taskQueue.empty();});

                    if (stopFlag && taskQueue.empty()) {
                        return;
                    }

                    curTask = std::move(taskQueue.front());
                    taskQueue.pop();
                    lock.unlock();
                    curTask();
                }
            });
        }
    }

    ~ThreadPool() noexcept {
        std::unique_lock<std::mutex> lock(mutexThread);
        stopFlag = true;
        lock.unlock();

        conditionVar.notify_all();
        for (auto &th : threadVector) {
            th.join();
        }
    }

    template <typename Func, typename... Args>
    auto exec(Func &&func, Args&&... args) -> std::future<decltype(func(args...))> {
        auto x = std::make_shared<std::packaged_task<decltype(func(args...))()>>
                (std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        std::future<decltype(func(args...))> futureRequest = x->get_future();
        std::unique_lock<std::mutex> lock(mutexThread);
        taskQueue.emplace([x]() {
            (*x)();
        });
        lock.unlock();
        conditionVar.notify_one();
        return futureRequest;
    }

private:
    bool stopFlag;
    std::mutex mutexThread;
    std::condition_variable conditionVar;
    std::vector<std::thread> threadVector;
    std::queue<std::function<void()>> taskQueue;
};

#endif
