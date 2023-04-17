#include "opencv_point_test.h"

#include <iostream>

using namespace std;

template<typename _Tp> inline
Point_<_Tp>::Point_()
    : x(0), y(0) {}

template<typename _Tp> inline
Point_<_Tp>::Point_(_Tp _x, _Tp _y)
    : x(_x), y(_y) {}


void putTextZH(Point org)
{
    if (org.x > 100 || org.y > 100) return;
    cout << "putTextZH" << endl;
}

void opencv_point_test()
{
    int left = 1;
    int top = 10;
    putTextZH(Point(left, top - 0.5 * 1 - 1));
}

