#pragma once
#include "Line.h"

template<typename T>
class Point {
    T x;
    T y;
public:
    Point(T x_, T y_): x(x_), y(y_) {}
    void move(T dx, T dy);
    void show() const;
    bool check(Line<T> const& l) const;
};