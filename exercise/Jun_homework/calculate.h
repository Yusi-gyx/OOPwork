#pragma once
#include "Fraction.h"
#include <iostream>
#include <type_traits>

template<typename T>
class calculate {
    T result;
public:
    calculate(char expressionType, int x, int y, int z)
    {
        //计算结果
        if constexpr(std::is_same_v<T, int>)
        {
            if (expressionType == 'A')
            {
                result = x * x + y * y + z * z;
            }
            else if (expressionType == 'B')
            {
                result = x * y + y / z - x * z;
            }
            else
            {
                result = y * 3 * z - x * z / (y - 2) - x * y / (z + 1);
            }
        }
        else if constexpr(std::is_same_v<T, Fraction>)
        {
            Fraction x_(x), y_(y), z_(z);
            if (expressionType == 'A')
            {
                result = x_ * x_ + y_ * y_ + z_ * z_;
            }
            else if (expressionType == 'B')
            {
                result = x_ * y_ + y_ / z_ - x_ * z_;
            }
            else
            {
                result = y_ * 3 * z_ - x_ * z_ / (y_ - 2) - x_ * y_ / (z_ + 1);
            }
        }
    }
    T getResult() const {return result;}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const calculate<T>& target)
{
    out << target.getResult();
    return out;
}