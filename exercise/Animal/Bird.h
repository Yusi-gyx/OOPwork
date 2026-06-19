#pragma once
#include "Animal.h"
#include <iostream>

class Bird: public Animal {
public:
    Bird(int color): Animal(color) {}
    void sing() override
    {
        std::cout << (getColor() == 0 ? "Red " : "Blue ")<< "bird is singing." << std::endl;
    }
    void swim() override
    {
        std::cout << "Bird can not swim." << std::endl;
    }
    ~Bird() {std::cout << (getColor() == 0 ? "Red " : "Blue ") << "bird is gone." << std::endl;}
};