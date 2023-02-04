#include "common.h"

#include <iostream>
#include <shared_mutex>
//#include <mutex>  // For std::unique_lock
#include <thread>

using namespace std;

class ThreadSafeCounter {
public:
    ThreadSafeCounter() = default;

    // Multiple threads/readers can read the counter's value at the same time.
    unsigned int get() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::cout << "get " << std::this_thread::get_id() << ' ' << value_ << '\n';
        return value_;
    }

    // Only one thread/writer can increment/write the counter's value.
    void increment() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_++;
        std::cout << "increment " << std::this_thread::get_id() << ' ' << value_ << '\n';
    }

    // Only one thread/writer can reset/write the counter's value.
    void reset() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_ = 0;
    }

private:
    mutable std::shared_mutex mutex_;
    unsigned int value_ = 0;
};

void shared_mutex_demo()
{
    cerr << "abc" << endl;

    ThreadSafeCounter counter;

    auto increment = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
        }
    };

    auto print = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.get();
        }
    };

    std::thread thread1(increment);
    std::thread thread2(print);
    std::thread thread3(print);

    thread1.join();
    thread2.join();
    thread3.join();
}