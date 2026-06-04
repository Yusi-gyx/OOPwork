#include "Line.h"
#include <iostream>
#include <cmath>

template<typename T>
bool Line<T>::intersect(const Line<T>& l) const
{
    if(std::abs(k - l.getk()) >= 1e-6) return true;    //斜率不相等
    if(std::abs(b - l.getb()) < 1e-6) return true;     //截距相等
    return false;
}

template<typename T> 
void Line<T>::show() const
{
    std::cout << k << "," << b << std::endl;
}

template<typename T>
bool Line<T>::operator<(const Line<T>& l) const
{
    if(std::abs(k - l.getk()) < 1e-6) return false;
    return k < l.getk();
}