#pragma once
#include <iostream>


    inline int gcd(int a, int b)
    {
        return b ? gcd(b, a % b) : a;
    }

class Fraction {
    long long int fenzi;
    long long int fenmu;
public:
    Fraction() {}
    Fraction(int fenzi_,int fenmu_ = 1):fenzi(fenzi_), fenmu(fenmu_) {}
    Fraction& operator+(int num);
    Fraction& operator-(int num);
    Fraction& operator*(const Fraction& p);
    Fraction& operator/(const Fraction& p);
    Fraction& operator+(const Fraction& p);
    Fraction& operator-(const Fraction& p);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& target)
    {
        out << target.fenzi << "/" << target.fenmu;
        return out;
    }
};