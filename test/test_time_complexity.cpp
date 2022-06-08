#if 0

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;
// O(n)
long long function1(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        k++;
    }
    return k;
}
// O(n^2)
void function2(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }

}
// O(nlogn)
void function3(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        for (long long j = 1; j < n; j = j * 2) { // 注意这里j=1
            k++;
        }
    }
}
int main() {
    long long n; // 数据规模
    while (1) {
        cout << "输入n：";
        cin >> n;
        auto tt = system_clock::now().time_since_epoch();

        milliseconds start_time = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
            );
        long long ret = function1(n);
        //function2(n);
        //function3(n);
        //this_thread::sleep_for(chrono::duration<long long, ratio<1, 1000>>(2000));
        //this_thread::sleep_for(milliseconds(2000));
        //this_thread::sleep_for(3000ms);
        
        auto tt2 = system_clock::now().time_since_epoch();
        auto tt3 = tt2 - tt;
        auto t4 = tt3.count();
        auto tt5 = duration_cast<milliseconds>(tt3);
        auto t6 = tt5.count();

        milliseconds end_time = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
            );

        cout << "ret = " << ret << endl;
        cout << "start_time:" << start_time.count() << endl;
        cout << "end_time:" << end_time.count() << endl;
        //cout << "耗时:" << end_time.count() - start_time.count() << " ms" << endl;
        cout << "耗时:" << t4 << " ms" << endl;
        cout << "耗时2:" << t6 << " ms" << endl;
    }
}

#endif