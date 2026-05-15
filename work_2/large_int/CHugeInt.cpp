#include"CHugeInt.h"
#include<cstring>
#include<algorithm>

CHugeInt& CHugeInt::operator=(const CHugeInt& other)
{
    delete[] num_1 ;
    num_1 = new char [strlen(other.num_1) + 1] ;
    strcpy(num_1, other.num_1) ;
    num_1 [strlen(other.num_1)] = '\0' ;
    return *this ;
}

CHugeInt CHugeInt::operator+(CHugeInt& other)
{
    int i = strlen(num_1) - 1 ;
    int j = strlen(other.num_1) - 1 ;
    int carry = 0 ;  //进位
    int k = max(strlen(num_1), strlen(other.num_1)) + 2 ;
    char* new_num = new char[k];
    int index = k - 2 ;
    
    while(i >= 0 || j >= 0 || carry != 0)
    {
        int m, n ;
        if(i >= 0) m = num_1[i --] - '0' ; else m = 0 ;
        if(j >= 0) n = other.num_1 [j --] - '0' ; else n = 0 ;
        int sum = m + n + carry ;
        new_num [index --] = '0' + (sum % 10) ;
        carry = sum / 10 ;
    }
    new_num [k - 1] = '\0';

    if(index == 0)  //没有发生进位
    {
        for(int t = 0 ; t < k - 2 ; t ++)
        {
            new_num [t] = new_num [t + 1] ;
        }
        new_num [k - 2] = '\0';
    }
    CHugeInt temp {new_num} ;
    delete[] new_num ;
    return temp ;
}

CHugeInt CHugeInt::operator+(int n)
{
    int k = n ; 
    int count = 0 ;
    while(k)
    {
        count ++ ;
        k /= 10 ;
    }
    char* num_n = new char[count + 1];
    for(int i = count - 1 ; i >= 0 ; i --)
    {
        num_n [i] = (n % 10) + '0' ;
        n /= 10 ;
    }
    num_n [count] = '\0';
    CHugeInt temp {num_n} ;
    delete[] num_n ;
    return *this + temp ;
}

ostream& operator<< (ostream& out, const CHugeInt& T)
{
    out << T.num_1 ;
    return out ;
}

CHugeInt& CHugeInt::operator++()
{
    *this = *this + 1 ;
    return *this ;
}

CHugeInt CHugeInt::operator++(int)
{
    CHugeInt temp = *this ;
    *this = *this + 1 ;
    return temp ;
}

CHugeInt& CHugeInt::operator+=(int n)
{
    CHugeInt temp = *this + n ;
    *this = temp ;
    return *this ;
}

CHugeInt operator+(int n, CHugeInt& T)
{
    return T + n ;
}