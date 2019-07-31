#include "common.h"

void bitOpDemo()
{
    int a = 0x0001 | 0x0010;
    int b = ~a;
    cout << hex << a << endl;
    cout << hex << b << endl;

}