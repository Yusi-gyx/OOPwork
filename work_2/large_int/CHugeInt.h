#pragma once
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 220; 
class CHugeInt {
    char* num_1 ;
public:
    CHugeInt(char* s)
    {
        num_1 = new char[strlen(s) + 1] ;
        strcpy(num_1, s) ;
        num_1 [strlen(s)] = '\0' ;
    }
    CHugeInt(int n)
    {
        int k = n ;
        int count = 0 ;
        while(k)
        {
            count ++ ;
            k /= 10 ;
        }
        char* num_2 = new char [count + 1] ;
        for(int i = count - 1 ; i >= 0 ; i --) 
        {
            num_2 [i] = (n % 10) + '0' ;
            n /= 10 ;
        }
        num_2 [count] = '\0' ;
        num_1 = new char [strlen(num_2) + 1] ;
        strcpy(num_1, num_2);
        num_1 [strlen(num_2)] = '\0' ;
        delete[] num_2 ;
    }
    CHugeInt(const CHugeInt& T)
    {
        num_1 = new char [strlen(T.num_1) + 1];
        strcpy(num_1, T.num_1) ;
        num_1 [strlen(T.num_1)] = '\0' ;
    }
    ~CHugeInt() 
    {
        delete[] num_1 ;
    }

    CHugeInt& operator=(const CHugeInt& other) ;

    CHugeInt operator+(CHugeInt& other) ;
    CHugeInt operator+(int n) ;

    friend ostream& operator <<(ostream& out, const CHugeInt& T) ;

    CHugeInt& operator++() ;
    CHugeInt operator++(int) ;

    CHugeInt& operator+=(int n) ;

    friend CHugeInt operator+(int n, CHugeInt& T) ;
};