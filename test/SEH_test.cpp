#include "common.h"

#include <iostream>

using namespace std;

void SEH_test() {
	__try {
		int a = 1;
		cout << "1" << endl;

		int* p = nullptr;
		//*p = 2;

		cout << "1-1" << endl;
		return;
		cout << "1-2" << endl;
	}
	__finally {
		cout << "2" << endl;
	}
	cout << "3" << endl;
}

void cpp_try_catch() {
	try {
		int a = 1;
		cout << "1" << endl;

		//int* p = nullptr;
		//*p = 2;
		int b = 0;
		int c = 3 / b;
		cout << "c" << c << endl;

		cout << "1-1" << endl;
		return;
		cout << "1-2" << endl;
	}
	catch(/*const exception& e*/...) {
		cout << "2" << endl;
		//cout << "exception:" << e.what() << endl;
	}
	cout << "3" << endl;
}