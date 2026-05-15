#pragma once
#include<iostream>

class Shape {
public:
    virtual double getArea()=0;
    virtual ~Shape()=default;
};

class Rectangle : public Shape {
    double width , height ;
public:
    Rectangle(double a, double b): width(a), height(b) {}
    double getArea() ;
} ;

class Circle : public Shape {
    double radius ;
public:
    Circle(double c): radius(c) {}
    double getArea() ;
} ;