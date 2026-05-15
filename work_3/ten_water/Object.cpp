#include "Object.h"
#include "Splash.h"
#include<iostream>

int Water::act(Direction fromwhere, Actor fromwho)
{
    int sum = 0 ;
    //先对改变的类型进行分类
    if(fromwho == WATER || fromwho == PLAYER)
    {
        weight += 1 ;
        if(weight == 4)   //水滴爆开
        {
            splash->map[x][y] = new Void(x, y, splash);
            sum += 1 ;
            
            if(x - 1 >= 0)
            {
                Object* target = splash->map[x - 1][y] ;
                sum += target->act(DOWN, WATER);
                if(target != splash->map[x - 1][y]) delete target ;   //处理对象的变化问题
            }
            if(x + 1 < splash->size)
            {
                Object* target = splash->map[x + 1][y] ;
                sum += target->act(UP, WATER);
                if(target != splash->map[x + 1][y]) delete target ;
            }
            if(y - 1 >= 0)
            {
                Object* target = splash->map[x][y - 1] ;
                sum += target->act(RIGHT, WATER);
                if(target != splash->map[x][y - 1]) delete target ;
            }
            if(y + 1 < splash->size)
            {
                Object* target = splash->map[x][y + 1] ;
                sum += target->act(LEFT, WATER);
                if(target != splash->map[x][y + 1]) delete target ;
            }
        }
    }   
    else if(fromwho == TOXIC)
    {
        weight -= 1 ;
        if(weight == 0)  //变成空地
        {
            splash->map [x][y] = new Void(x, y, splash);
        }
    }
    // std::cout << sum << std::endl ;
    return sum ;
}

int Void::act(Direction fromwhere, Actor fromwho)
{
    int sum = 0;
    if(fromwho == PLAYER)
    {
        std::cout << "Error: Cannot act a Void." << std::endl ;
    }
    else if(fromwho == WATER)  //有水滴传过来
    {
        if(fromwhere == DOWN && x - 1 >= 0)
        {
            Object* target = splash->map[x - 1][y];
            sum += target->act(DOWN, WATER);
            if(target != splash->map[x - 1][y]) delete target ;
        }
        else if(fromwhere == UP && x + 1 < splash->size)
        {
            Object* target = splash->map[x + 1][y];
            sum += target->act(UP, WATER);
            if(target != splash->map[x + 1][y]) delete target ;
        }
        else if(fromwhere == RIGHT && y - 1 >= 0)
        {
            Object* target = splash->map[x][y - 1];
            sum += target->act(RIGHT, WATER);
            if(target != splash->map[x][y - 1]) delete target ;
        }
        else if(fromwhere == LEFT && y + 1 < splash->size)
        {
            Object* target = splash->map[x][y + 1];
            sum += target->act(LEFT, WATER);
            if(target != splash->map[x][y + 1]) delete target ;
        }  
    }
    else if(fromwho == TOXIC)  //有毒液传过来
    {
        if(fromwhere == DOWN && x - 1 >= 0)
        {
            Object* target = splash->map[x - 1][y];
            sum += target->act(DOWN, TOXIC);
            if(target != splash->map[x - 1][y]) delete target ;
        }
        else if(fromwhere == UP && x + 1 < splash->size)
        {
            Object* target = splash->map[x + 1][y];
            sum += target->act(UP, TOXIC);
            if(target != splash->map[x + 1][y]) delete target ;
        }
        else if(fromwhere == RIGHT && y - 1 >= 0)
        {
            Object* target = splash->map[x][y - 1];
            sum += target->act(RIGHT, TOXIC);
            if(target != splash->map[x][y - 1]) delete target ;
        }
        else if(fromwhere == LEFT && y + 1 < splash->size)
        {
            Object* target = splash->map[x][y + 1];
            sum += target->act(LEFT, TOXIC);
            if(target != splash->map[x][y + 1]) delete target ;
        }
    }
    return sum ;
}

int Barrier::act(Direction fromwhere, Actor fromwho)
{
    if(fromwho == PLAYER)
    {
        std::cout << "Error: Cannot act a Barrier." << std::endl ;
    }
    return 0 ;

}

int Toxic::act(Direction fromwhere, Actor fromwho)
{
    int sum = 0 ;
    if(fromwho == TOXIC || fromwho == PLAYER)
    {
        weight += 1 ;
        if(weight == 4)   //毒液爆开
        {
            splash->map[x][y] = new Void(x, y, splash) ;
            sum -= 1 ;

            if(x - 1 >= 0)
            {
                Object* target = splash->map[x - 1][y] ;
                sum += target->act(DOWN, TOXIC);
                if(target != splash->map[x - 1][y]) delete target ;
            }
            if(x + 1 < splash->size)
            {
                Object* target = splash->map[x + 1][y] ;
                sum += target->act(UP, TOXIC);
                if(target != splash->map[x + 1][y]) delete target ;
            }
            if(y - 1 >= 0)
            {
                Object* target = splash->map[x][y - 1] ;
                sum += target->act(RIGHT, TOXIC);
                if(target != splash->map[x][y - 1]) delete target ;
            }
            if(y + 1 < splash->size)
            {
                Object* target = splash->map[x][y + 1] ;
                sum += target->act(LEFT, TOXIC);
                if(target != splash->map[x][y + 1]) delete target ;
            }
        }
    }
    else
    {
        weight -= 1 ;
        if(weight == 0)  //变成空地
        {
            splash->map[x][y] = new Void(x, y, splash) ;
        }
    }
    // std::cout << sum << std::endl;
    return sum ;
}