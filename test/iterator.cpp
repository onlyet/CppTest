#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    //vector<int> v{ 1,2,3,4,5,6,7,8,9 };
    //for (const auto& e : v) {
    //    cout << e << " ";
    //}
    //cout << endl;

    //for (auto it = v.begin(), end = v.end(); it != end; ) {
    //    if (*it == 3) {
    //        //v.erase(it);
    //        //cout << "after erase: " << *it << endl;
    //        v.push_back(*it);
    //    }
    //    ++it;
    //}

    //for (const auto& e : v) {
    //    cout << e << " ";
    //}
    //cout << endl;

    int i = 49149;
    int j = i * i;
    unsigned int k = i * i;
    long long l = i * i;
    unsigned long long m = i * i;

    long long i2 = 49149;
    long long n = i2 * i2;
    long long o = i2 * i2;

    cout << "i: " << i << endl;
    cout << "j: " << j << endl;
    cout << "k " << k << endl;
    cout << "l: " << l << endl;
    cout << "m: " << m << endl;

    cout << "n: " << n << endl;
    cout << "o: " << o << endl;


    //long long a = 49149 * 49149;
    //printf("%lld\n", a);

    long long a = (long long)49149 * 49149;
    cout << "a: " << a << endl;

    return 0;
}