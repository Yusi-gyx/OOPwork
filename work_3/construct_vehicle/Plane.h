#include"Vehicle.h"
#include<iostream>

class Plane: public Vehicle {
public:
    Plane()
    {
        set_max_wheel_num(3);
        set_max_wing_num(2);
    }
    void run()
    {
        std::cout << "I am running and flying" << std::endl ;
    }
};