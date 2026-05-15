#pragma once
#include "smithing_stone.h"
#include <iostream>

class SomberSmithingStone: public SmithingStone {
public:
    SomberSmithingStone(int level, int amount): SmithingStone(level)
    {
        std::cout << "Somber smithing stone " << level << " was created." << std::endl ;
        add(amount) ;
    }
    ~SomberSmithingStone()
    {
        std::cout << "Somber smithing stone " << get_level() << " was destroyed." << std::endl ;
    }
    void add(int amount)
    {
        add_amount(amount) ;
        std::cout << "Somber smithing stone " << get_level() << " was added with " << amount << "." << std::endl ; 
    }
    bool subtract(int amount)
    {
        add_amount((-1) * amount) ;
        std::cout << "Somber smithing stone " << get_level() << " was subtracted with " << amount << "." << std::endl ;
        return greater_equal(1) ;   //当数量大于等于1时才返回true，故当数量为0时就返回false析构对象
    }
    bool check_stock(int n)
    {
        return greater_equal(n) ;
    }
} ;