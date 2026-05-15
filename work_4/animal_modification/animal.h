#pragma once

#include <string>
#include <iostream>

class Animal {
public:
    std::string name ;
    Animal(std::string a): name(a) {}
    virtual ~Animal() {} ;
    virtual void speak() {}
    virtual void swim() {}
    void action()
    {
        speak() ;
        swim() ;
    }
} ;