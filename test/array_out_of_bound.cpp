#if 0
#include "common.h"
#include <time.h>

#include <iostream>
using namespace std;

template<typename T>
int get_max_digit(T arr[], int len) {
    int max_digit = 1;
    for (int i = 0; i < len; ++i) {
        int digit = 1;
        int j = 10;
        while (arr[i] / j) {
            ++digit;
            j *= 10;
        }
        if (digit > max_digit) {
            max_digit = digit;
        }
    }
    return max_digit;
}

//template<typename T>
void radix_sort(int arr[], int len) {
    int radix = get_max_digit(arr, len);
    int count_arr[10] = { 0 };
    int* tmp_arr = new int[len];
    //for (int i = 0; i < len; ++i) {
    //    tmp_arr[i] = 0;
    //}
    int s = 1;

    for (int r = 0; r < radix; ++r) {
        for (int i = 0; i < len; ++i) {
            ++count_arr[arr[i] / s % 10];
        }
        for (int i = 1; i < 10; ++i) {
            count_arr[i] += count_arr[i - 1];
        }
        for (int i = 0; i < len; ++i) {
            int j = arr[i] / s % 10;
            int tt = count_arr[j] - 1;
            if (tt > len) {
                cout << "out of index" << endl;
                return;
            }
            tmp_arr[tt] = arr[i];
            --count_arr[j];
        }
        //for (int i = 0; i < len; ++i) {
        //    cout << tmp_arr[i];
        //}
        for (int i = 0; i < len; ++i) {
            arr[i] = tmp_arr[i];
        }
        s *= 10;
    }

    delete[] tmp_arr;
}


void array_out_of_bound_test() {
    //char* src = new char[7];
    //src[7] = 'g';
    //delete[] src;

    //int* arr = new int[10];
    //arr[0] = 1;
    //arr[1] = 2;
    //arr[115] = 1;
    //delete[] arr;

    int len = 20;
    int* a = new int[len];
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        a[i] = rand() % 400;
    }

    cout << "Before sorted:";
    for (int i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    radix_sort(a, len);

    cout << " After sorted:";
    for (int i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

#endif