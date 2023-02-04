#include "common.h"
#include <assert.h>
#include <thread>
#include <atomic>

using namespace std;





//std::atomic<int> data1;
//std::atomic<bool> flag;
//void thread1() {
//    data1.store(42, std::memory_order_relaxed);
//    flag.store(true, std::memory_order_release);
//    cout << "flag = true" << endl;
//}
//
//void thread2() {
//    while (!flag.load(std::memory_order_acquire)) {
//    }
//    assert(data1.load(std::memory_order_relaxed) == 42);
//    cout << "done" << endl;
//}

//std::atomic<int> data1;
//std::atomic<bool> flag;
//void thread1() {
//    data1 = 42;
//    flag = true;
//    cout << "flag = true" << endl;
//}
//
//void thread2() {
//    while (!flag) {
//    }
//    assert(data1 == 42);
//    cout << "done" << endl;
//}

//class spinlock_mutex
//{
//    std::atomic_flag flag = ATOMIC_FLAG_INIT;
//public:
//    spinlock_mutex()/* :
//        flag(ATOMIC_FLAG_INIT)*/
//    {}
//    void lock()
//    {
//        while (flag.test_and_set(std::memory_order_acquire))
//        {
//            this_thread::sleep_for(1us);
//        }
//    }
//    void unlock()
//    {
//        flag.clear(std::memory_order_release);
//    }
//};
//
//spinlock_mutex spinLock;
//
//void thread1() {
//    spinLock.lock();
//    cout << "lock, " << this_thread::get_id()  << endl;
//    this_thread::sleep_for(300s);
//}
//void thread2() {
//    spinLock.lock();
//    cout << "lock, " << this_thread::get_id() << endl;
//}

int data1 = 0;
volatile bool flag = false;
void thread1() {
    flag = true;
    data1 = 42;
    cout << "flag = true" << endl;
}

// msvc2017 优化/O2：thread2一直在while循环内执行
void thread2() {
    while (!flag) {
    }
    assert(data1 == 42);
    cout << "done" << endl;
}

void aotmic_demo()
{
    thread t2(&thread2);
    thread t1(&thread1);

    t2.join();
    t1.join();
}