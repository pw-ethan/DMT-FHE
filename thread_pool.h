#ifndef THREAD_POOL_H
#define THREAD_POOL_H


#include <functional>
#include <atomic>
#include <vector>
#include <thread>
#include <future>
#include "threadsafe_queue.h"
#include "join_threads.h"
#include "function_wrapper.h"


class CThreadPool {
    std::atomic_bool done;
    threadsafe_queue<function_wrapper> work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void worker_thread() {
        while (!done) {
            function_wrapper task;
            if (work_queue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

public:
    CThreadPool() : done(false), joiner(threads) {
        unsigned const thread_count = std::thread::hardware_concurrency();

        try {
            for (unsigned i = 0; i < thread_count; ++i) {
                threads.push_back(std::thread(&CThreadPool::worker_thread, this));
            }
        } catch (...) {
            done = true;
            throw;
        }
    }

    ~CThreadPool() {
        done = true;
    }

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) {
        typedef typename std::result_of<FunctionType()>::type result_type;

        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        work_queue.push(std::move(task));
        return res;
    }
};


#endif // THREAD_POOL_H
