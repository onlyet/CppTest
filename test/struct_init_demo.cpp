#include "common.h"

#include <iostream>
using namespace std;

struct StructInitTest
{
    int a;
    char b;
    int c;
};

struct StructInitTestBracket
{
    int a;
    char b;
    int c;
};

void StructInitTestDemo()
{
    StructInitTestBracket *s2 = new StructInitTestBracket();
    cout << s2->a << ", " << s2->b << s2->c << endl;

    StructInitTest *s = new StructInitTest;
    cout << s->a << ", " << s->b << s->c << endl;
}