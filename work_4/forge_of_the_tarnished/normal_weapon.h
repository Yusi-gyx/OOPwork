#pragma once 
#include "weapon.h"
#include <iostream>

class NormalWeapon: public Weapon {
public:
    NormalWeapon(string name): Weapon(name)
    {
        std::cout << "Normal weapon " << name << " was created." << std::endl ; 
    }
    ~NormalWeapon()
    {
        std::cout << "Normal weapon " << get_name() ;
        if(get_level() != 0) std::cout << "+" << get_level() ;
        std::cout << " was destroyed." << std::endl ;
    }
    bool check_name(string name)
    {
        return name == get_name() ;
    }
    bool check_level(int target)
    {
        return  target > get_level() ;
    }
    void _upgrade()
    {
        upgrade() ;
        std::cout << "Normal weapon " << get_name() ;
        if(get_level() - 1 != 0) std::cout << "+" << get_level() - 1 ;
        std::cout << " was upgraded to " << get_name() << "+" << get_level() << "." << std::endl ;
    }
    int getLevel()
    {
        return get_level() ;
    }
} ;