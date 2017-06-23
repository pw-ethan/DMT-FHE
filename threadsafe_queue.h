#ifndef THREADSAFE_QUEUE_H_INCLUDED
#define THREADSAFE_QUEUE_H_INCLUDED

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mut;
    // std::queue<T> data_queue; // version 1
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;

public:
    threadsafe_queue() {}
    threadsafe_queue(const threadsafe_queue& other) {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }
    threadsafe_queue& operator=(const threadsafe_queue&) = delete; // don't allow operator=

    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
//        data_queue.push(std::move(new_value));
        data_queue.push(data);
        data_cond.notify_one();
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) {
            return false;
        }
//        value = std::move(data_queue.front());
        value = std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) {
            return std::shared_ptr<T>();
        }
//        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
//        value = std::move(data_queue.front());
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
//        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

#endif // THREADSAFE_QUEUE_H_INCLUDED
