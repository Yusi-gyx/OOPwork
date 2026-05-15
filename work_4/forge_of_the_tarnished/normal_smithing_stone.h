#pragma once 
#include "smithing_stone.h"
#include <iostream>

class NormalSmithingStone: public SmithingStone {
public:
    NormalSmithingStone(int level, int amount): SmithingStone(level)
    {
        std::cout << "Normal smithing stone " << level << " was created." << std::endl ;
        add(amount) ;
    }
    ~NormalSmithingStone()
    {
        std::cout << "Normal smithing stone " << get_level() << " was destroyed." << std::endl ;
    }
    void add(int amount)
    {
        add_amount(amount) ;
        std::cout << "Normal smithing stone " << get_level() << " was added with " << amount << "." << std::endl ;
    }
    bool subtract(int amount)
    {
        add_amount((-1) * amount) ;
        std::cout << "Normal smithing stone " << get_level() << " was subtracted with " << amount << "." << std::endl ;
        return greater_equal(1) ;
    }
    bool check_stock(int n)
    {
        return greater_equal(n) ;
    }
} ;