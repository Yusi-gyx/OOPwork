#include "Fraction.h"

Fraction &Fraction::operator+(int num)
{
    fenzi += num * fenmu;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}
Fraction &Fraction::operator-(int num)
{
    fenzi -= num * fenmu;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}
Fraction &Fraction::operator*(const Fraction &p)
{
    fenzi = fenzi * p.fenzi ;
    fenmu = fenmu * p.fenmu;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}
Fraction &Fraction::operator/(const Fraction &p)
{
    fenzi = fenzi * p.fenmu ;
    fenmu = fenmu * p.fenzi;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}

Fraction &Fraction::operator+(const Fraction &p)
{
    fenzi = fenzi * p.fenmu + fenmu * p.fenzi ;
    fenmu = fenmu * p.fenmu;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}
Fraction &Fraction::operator-(const Fraction &p)
{
    fenzi = fenzi * p.fenmu - fenmu * p.fenzi ;
    fenmu = fenmu * p.fenmu;
    long long int mod = gcd(fenzi, fenmu);
    fenzi /= mod;
    fenmu /= mod;
    return *this;
}