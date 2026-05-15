#include "tarnished.h"
#include <iostream>

Tarnished::Tarnished() 
{
    for(int i = 0 ; i < MAX_STONES ; i ++)
    {
        normal_smithing_stones [i] = nullptr ;
        somber_smithing_stones [i] = nullptr ;
    }
    for(int i = 0 ; i < MAX_WEAPONS ; i ++)
    {
        normal_weapons [i] = nullptr ;
        somber_weapons [i] = nullptr ;
    }
}

Tarnished::~Tarnished()  //按照顺序进行析构（删除动态构造的内存）
{
    for(int i = 1 ; i < MAX_STONES ; i ++)
    {
        if(normal_smithing_stones [i] != nullptr) delete normal_smithing_stones [i] ;
    }
    for(int i = 1 ; i < MAX_STONES ; i ++)
    {
        if(somber_smithing_stones [i] != nullptr) delete somber_smithing_stones [i] ;
    }
    for(int i = 0 ; i < MAX_WEAPONS ; i ++)
    {
        if(normal_weapons [i] != nullptr) delete normal_weapons [i] ;
    }
    for(int i = 0 ; i < MAX_WEAPONS ; i ++)
    {
        if(somber_weapons [i] != nullptr) delete somber_weapons [i] ;
    }
}

void Tarnished::pick_up_stone(int type, int level, int number)
{
    if(type == 0)  //普通锻造石
    {
        if(normal_smithing_stones [level] != nullptr)   //已经有这种锻造石了
        {
            normal_smithing_stones [level]->add(number) ;
        }
        else  //还没有这种锻造石
        {
            normal_smithing_stones [level] = new NormalSmithingStone(level, number) ;
        }
    }
    else  //失色锻造石
    {
        if(somber_smithing_stones [level] != nullptr) 
        {
            somber_smithing_stones [level] ->add(number);
        }
        else
        {
            somber_smithing_stones [level] = new SomberSmithingStone(level, number) ;
        }
    }
}

void Tarnished::pick_up_weapon(int type, string name)
{
    int target = 0 ;
    if(type == 0)  //普通武器
    {
        for(int i = 0; i < MAX_WEAPONS; i++)
        {
            if (normal_weapons [i] == nullptr) 
            {
                target = i ;
                break ;
            } 
        }
        normal_weapons [target] = new NormalWeapon(name) ;
    }
    else   //失色武器
    {
        for(int i = 0; i < MAX_WEAPONS; i ++)
        {
            if(somber_weapons [i] == nullptr)
            {
                target = i ;
                break ;
            }
        }
        somber_weapons [target] = new SomberWeapon(name) ;
    }
}

void Tarnished::upgrade_weapon(int target, string name)
{
    int index = -1 ;
    int type = -1 ;
    for(int i = 0 ; i < MAX_WEAPONS; i ++)  //寻找普通武器
    {
        if(normal_weapons [i] != nullptr)
        {
            if(normal_weapons [i]->check_name(name)) 
            {
                index = i ;
                type = 0 ;
                break ;
            }
        }
    }
    if(index == -1)   //继续寻找失色武器
    {
        for(int i = 0 ; i < MAX_WEAPONS; i ++)
        {
            if(somber_weapons [i] != nullptr)
            {
                if(somber_weapons [i]->check_name(name)) 
                {
                    index = i ;
                    type = 1 ;
                    break ;
                }
            }
        }
    }

    if(index == -1) //没有这件武器
    {
        std::cout << "You don't have the right!" << std::endl ;
        return ;
    }

    if(type)    //升级失色武器
    {
        int original_level = somber_weapons [index]->getLevel() ;
        if(!somber_weapons [index]->check_level(target))
        {
            std::cout << "Stay calm!" << std::endl ;
            return ;
        }
        for(int i = somber_weapons [index]->getLevel() ; i < target ; i ++)
        {
            int m = i + 1 ;  //要用到的锻造石的等级
            int n = 1 ;  //要用到的锻造石的数量
            if(somber_smithing_stones [m] == nullptr) 
            {
                std::cout << "Upgrade failed for lacking somber smithing stone " << m << "." << std::endl ;
                return ;
            }
            if(!somber_smithing_stones [m] ->check_stock(n))
            {
                std::cout << "Upgrade failed for lacking somber smithing stone " << m << "." << std::endl ;
                return ;
            }
        }
        //数量检查通过，进行升级
        for(int i = somber_weapons [index]->getLevel() ; i < target ; i ++)
        {
            int m = i + 1 ;  //要用到的锻造石的等级
            int n = 1 ;  //要用到的锻造石的数量
            if(!somber_smithing_stones [m]->subtract(n))   //先减少锻造石的数量
            {
                delete somber_smithing_stones [m] ;
                somber_smithing_stones [m] = nullptr ;
            }
            somber_weapons [index]->_upgrade() ;
        }
        std::cout << "Upgrade " << name ;
        if(original_level != 0) std::cout << "+" << original_level ;
        std::cout << " to " << name << "+" << somber_weapons [index]->getLevel() << " Successfully." << std::endl ;
    }
    else       //升级普通武器
    {
        int original_level = normal_weapons [index]->getLevel() ;
        if(!normal_weapons [index]->check_level(target))
        {
            std::cout << "Stay calm!" << std::endl ;
            return ;
        }
        int need [25]= {0} ;   //储存对每一级锻造石的需求
        for(int i = normal_weapons [index]->getLevel() ; i < target ; i ++)
        {
            int m = i/3 + 1 ;  //要用到的锻造石的等级
            int n = (i % 3 + 1) * 2 ;  //要用到的锻造石的数量
            need [m] += n ;
            if(normal_smithing_stones [m] == nullptr)    //如果完全没有这个等级的锻造石肯定不能升级
            {
                std::cout << "Upgrade failed for lacking normal smithing stone " << m << "." << std::endl ;
                return ;
            }
            // if(!normal_smithing_stones [m] ->check_stock(n))
            // {
            //     std::cout << "Upgrade failed for lacking normal smithing stone " << m << "." << std::endl ;
            //     return ;
            // }
        }
        for(int i = 1 ; i < 25 ; i ++)
        {
            if(need [i] == 0) continue ;
            if (!normal_smithing_stones[i]->check_stock(need[i]))
            {
                std::cout << "Upgrade failed for lacking normal smithing stone " << i << "." << std::endl;
                return;
            }
        }
        //数量检查通过，进行升级
        for(int i = normal_weapons [index]->getLevel() ; i < target ; i ++)
        {
            int m = i/3 + 1 ;  //要用到的锻造石的等级
            int n = (i % 3 + 1) * 2 ;  //要用到的锻造石的数量
            if(!normal_smithing_stones [m]->subtract(n))   //先减少锻造石的数量
            {
                delete normal_smithing_stones [m] ;
                normal_smithing_stones [m] = nullptr ;
            }
            normal_weapons [index]->_upgrade() ;
        }
        std::cout << "Upgrade " << name ;
        if(original_level != 0) std::cout << "+" << original_level ;
        std::cout << " to " << name << "+" << normal_weapons [index]->getLevel() << " Successfully." << std::endl ;
    }
}