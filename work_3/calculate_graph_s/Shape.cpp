#include"Shape.h"
#include<iostream>

double Rectangle::getArea()
{
    return width*height ;
}

double Circle::getArea()
{
    return 3.14*radius*radius ;
}