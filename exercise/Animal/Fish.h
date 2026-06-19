#pragma once
#include "Animal.h"
#include <iostream>

class Fish: public Animal {
public:
    Fish(int color): Animal(color) {}
    void swim() override
    {
        std::cout << (getColor() == 0? "Red " : "Blue ") << "fish is swimming." << std::endl;
    }
    void sing() override
    {
        std::cout << "Fish can not sing." << std::endl;
    }
    ~Fish() {std::cout << (getColor() == 0 ? "Red " : "Blue ") << "fish is gone." << std::endl;}
};