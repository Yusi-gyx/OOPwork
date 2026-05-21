#pragma once
#include "BasicContainer.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using std::vector;
using std::map;

template<class A>
struct Point {
    Pos pos;
    A value;
    Point (Pos p, A v): pos(p), value(v) {}
    bool operator<(const Point& other)
    {
        return pos < other.pos;
    }
};


//map的版本
template<class A, class C>
class Container : public BasicContainer<A> {
    map<Pos, A> base;
public:
    void insert(const Pos &p, const A &v) 
    {
        base [p] = v;
    }
    A* find(Pos p) 
    {
        auto it = base.find(p);
        if(it != base.end()) return &(it->second);
        else return nullptr;
    }
};


//vector的版本
template <class A>
class Container<A, vector<A> > : public BasicContainer<A> {
    vector< Point<A> > base;
    bool sorted = false;
public:
    void insert(const Pos &p, const A &v) {
        base.push_back(Point<A>(p, v));
    }

    A* find(Pos p) {
        if(!sorted)
        {
            std::sort(base.begin(), base.end());   //对vector进行排序
            sorted = true;
        }
        auto low = std::lower_bound(base.begin(), base.end(), p, [](const Point<A> target, const Pos obj){
            return target.pos < obj;
        });
        if(low != base.end() && low->pos == p) return &(low->value);
        else return nullptr;

        // for(auto t = base.begin(); t != base.end(); ++t) {
        //     if(p == t->pos) return &(t->value);
        // }
        // return NULL;
    }
};