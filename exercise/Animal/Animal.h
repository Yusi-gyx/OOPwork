#pragma once

class Animal {
    int color;
public:
    Animal(int color_): color(color_) {}
    virtual void swim() = 0;
    virtual void sing() = 0;
    int getColor() const {return color;}
    virtual ~Animal() = default;
};