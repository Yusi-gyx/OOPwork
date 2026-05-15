#pragma once
#include <vector>
template <typename T>
class Switch {
    T flag_ ;
    void(*op)(int&) ;
    bool shouldBreak_ ;
public:
    Switch(T flag, void(*op_)(int&), bool shouldBreak):flag_(flag), op(op_), shouldBreak_(shouldBreak) {}
    T getFlag() const {return flag_ ;}
    void operation(int& target) const
    {
        op(target) ;
    }
    bool whetherBreak() const {return shouldBreak_ ;}
} ;

template <typename T>
class MySwitch {
    std::vector<Switch<T>> cases ;
public:
    MySwitch() {}
    void addCase(T flag, void(*op)(int&), bool shouldBreak)
    {
        cases.emplace_back(flag, op, shouldBreak) ;
    }
    void execute(T value, int& target)
    {
        for(auto& c : cases)
        {
            if(value == c.getFlag())
            {
                c.operation(target) ;
                if(c.whetherBreak()) break ;
            }
        }
    }
} ;