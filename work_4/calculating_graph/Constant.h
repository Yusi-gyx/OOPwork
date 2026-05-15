#pragma once
#include "Value.h"

class Constant : public Value {
    int num ;
public:
    Constant(int a): num(a) {}
    int calc() 
    {
        return num ;
    }
    void setNum(int b)
    {
        num = b ;
    }
    ~Constant() {}
} ;