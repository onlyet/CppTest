#include "common.h"
#include <thread>
#include <iostream>

using namespace std;

static bool s_isrun = true;

void thread_process() {
	int ww = 1920, hh = 1080;
	thread t([](int w, int h) {
		while (s_isrun) {
			int sum = w + h;
			cout << "sum: " << sum << endl;
			this_thread::sleep_for(1s);
		}
		}, ww, hh);

	cout << "start detach" << endl;
	t.detach();
	cout << "stop detach" << endl;
}

void thread_test() {
	cout << "thread_test 1" << endl;
	thread_process();
	while (1) {
		int a = 1 + 1;
	}
	cout << "thread_test 2" << endl;
}