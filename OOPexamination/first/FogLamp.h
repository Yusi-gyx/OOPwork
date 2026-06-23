#ifndef FOGLAMP_H
#define FOGLAMP_H

#include <string>
#include <iostream>

class Lamp {
    std::string color;
public:
    Lamp(std::string color_):color(color_) {}
    const std::string& getColor() const {return color;}
    virtual void up(int d) = 0;
    virtual int power() const = 0;
    virtual std::string report() const = 0;
    virtual Lamp* clone() const = 0;
    virtual ~Lamp() {}
};

class SteadyLamp: public Lamp {
    int level;
public:
    SteadyLamp(std::string color_, int level_):Lamp(color_), level(level_) {}
    void up(int d) override
    {
        level += d;
    }
    int power() const override
    {
        return level;
    }
    std::string report() const
    {
        std::string re("S:");
        re += getColor();
        re += ":";
        re += std::to_string(level);
        return re;
    }
    Lamp* clone() const
    {
        return new SteadyLamp(getColor(), level);
    }
};

class PulseLamp:public Lamp {
    int low;
    int high;
public:
    PulseLamp(std::string color_, int low_, int high_):Lamp(color_), low(low_), high(high_) {}
    void up(int d) override
    {
        low += d;
        high += d;
    }
    int power() const override
    {
        return (low + high) / 2;
    }
    std::string report() const
    {
        std::string re("P:");
        re += getColor();
        re += ":";
        re += std::to_string(low);
        re += "-";
        re += std::to_string(high);
        return re;
    }
    Lamp* clone() const 
    {
        return new PulseLamp(getColor(), low, high);
    }
};



class Inspection {
private:
    Lamp* owned;
    Lamp* observed;
    bool frozen;

    const Lamp* current() const {
        return frozen ? owned : observed;
    }

public:
    Inspection(Lamp* lamp, bool frozen_): frozen(frozen_)     //一定要记得给所有成员进行初始化
    {
        if(frozen_)
        {
            owned = lamp -> clone();
            observed = nullptr;
        }
        else
        {
            observed = lamp;
            owned = nullptr;
        }
    }

    Inspection(const Inspection& other)
    {
        if(other.frozen)
        {
            owned = other.owned -> clone(); 
            observed = nullptr;
        }
        else
        {
            observed = other.observed;
            owned = nullptr;
        }
        frozen = other.frozen;
    }

    Inspection& operator=(const Inspection& other)
    {
        if(this == &other) return *this;
        if(frozen) delete owned;
        if(other.frozen)
        {
            owned = other.owned -> clone();
            observed = nullptr;
        }
        else 
        {
            observed = other.observed;
            owned = nullptr;
        }
        frozen = other.frozen;
        return *this;
    }

    ~Inspection()
    {
        if(frozen)
        {
            delete owned;
        }
    }

    std::string report()
    {
        std::string re;
        if(frozen) re = owned -> report();
        else re = observed -> report();
        return re;
    }

    int power()
    {
        int p;
        if(frozen) p = owned -> power();
        else p = observed -> power();
        return p ;
    }
};

#endif