#include "Point.h"
#include <iostream>
#include <cmath>

template<typename T>
void Point<T>::move(T dx, T dy)
{
    x += dx;
    y += dy;
}

template<typename T>
void Point<T>::show() const
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}

template<typename T>
bool Point<T>::check(Line<T> const& l) const
{
    if(std::abs(y - (l.getk() * x + l.getb())) < 1e-6) return true;
    return false;
}