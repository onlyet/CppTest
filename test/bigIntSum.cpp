#include "common.h"

void bigIntSum() {
	int i = 2000000000, j = 2000000000;
	int sum0 = i + j;
	cout << "sum:" << sum0 << endl;
	long long sum = (long long)i + j;
	cout << "long long sum:" << sum << endl;
}