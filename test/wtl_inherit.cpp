#include "common.h"
#include "wtl_inherit.h"

void wtl_inherit_demo()
{
    D1 d1;
    D2 d2;

    d1.SayHi();    // prints "This is B1"
    d2.SayHi();    // prints "This is D2"

}

