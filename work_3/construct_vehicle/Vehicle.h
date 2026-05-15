#pragma once
#include<iostream>

class Vehicle {
    int wing = 0, wheel = 0 ;
    int max_wing_num = 0, max_wheel_num = 0;
public:
    virtual ~Vehicle(){}
    void set_max_wheel_num(int i)
    {
        max_wheel_num = i ;
    }
    void set_max_wing_num(int j)
    {
        max_wing_num = j ;
    }
    void add_wheel() {wheel ++ ;}
    void add_wing() {wing ++ ;}
    bool finished()
    {
        if(wheel >= max_wheel_num && wing >= max_wing_num) return true ;
        else return false ;
    }
    virtual void run()
    {
        std::cout << "I am running" << std::endl ;
    }
};