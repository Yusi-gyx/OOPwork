#ifndef MY_LIB_H
#define MY_LIB_H

#include <iostream>
#include<string>

void print();   //无参数输出空行

void print(int x);

void print(bool x);

void print(std::string s) ;   //输出字符串

void print(const char* s);

void print(char c);

std::string input();

class Array {
    int size{};
    int a[100]{};
public:
    void append(int x);

    void pop();

    int getSize(); 

    int & operator[](int index)
    {
        return a [index] ;
    }
};

void print(Array a);



#endif
