#include "common.h"
#include <sstream>

using namespace std;

void ostringstreamDemo()
{
    string str("hello");
    ostringstream os1(str, ios_base::out);
    ostringstream os2(str, ios_base::ate);
    os1 << "\r\n" << "how are you";
    os2 << "\r\n" << "how are you";

    cout << os1.str() << endl;
    cout << os2.str() << endl;
}