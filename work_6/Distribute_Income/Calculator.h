#pragma once
#include <string>
#include "OccupationStrategy.h"
#include "PayStrategy.h"

class Calculator {		
    OccupationStrategy* my_occupation;
    PayStrategy* my_pay;						
public:
    Calculator(OccupationStrategy* _occu, PayStrategy* _pay): my_occupation(_occu), my_pay(_pay) {}
    double getSalary(double base, double bonus, double level)
    {
        return my_occupation -> getSalary(base, bonus, level);
    }
    double pay(std::string name, double money)
    {
        return my_pay -> pay(name, money);
    }
};