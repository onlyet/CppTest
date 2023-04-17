#pragma once


#ifndef OPENCV_ABI_COMPATIBILITY
#define OPENCV_ABI_COMPATIBILITY 400
#endif

#    define CV_NOEXCEPT noexcept


template<typename _Tp> class Point_
{
public:
    typedef _Tp value_type;

    //! default constructor
    Point_();
    Point_(_Tp _x, _Tp _y);
#if (defined(__GNUC__) && __GNUC__ < 5) && !defined(__clang__)  // GCC 4.x bug. Details: https://github.com/opencv/opencv/pull/20837
    Point_(const Point_& pt);
    Point_(Point_&& pt) CV_NOEXCEPT = default;
#elif OPENCV_ABI_COMPATIBILITY < 500
    Point_(const Point_& pt) = default;
    Point_(Point_&& pt) CV_NOEXCEPT = default;
#endif

    _Tp x; //!< x coordinate of the point
    _Tp y; //!< y coordinate of the point
};

typedef Point_<int> Point2i;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;


void putTextZH(Point org_);

//void opencv_point_test();