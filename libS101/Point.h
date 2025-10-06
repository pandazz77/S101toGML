#pragma once

template <typename T>
struct TPoint{
    T x;
    T y;
    TPoint() : x(0), y(0) {}
    TPoint(T xx, T yy): x(xx), y(yy) {}
};

typedef TPoint<long> Point;