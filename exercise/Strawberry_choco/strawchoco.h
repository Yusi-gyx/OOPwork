#pragma once
#include <set>
#include <vector>
#include "event.h"

class Chocolate: public EventInterface {
public:
    std::vector<EventInterface*> visited_zoo;
    Chocolate(): EventInterface() {}
    ~Chocolate() {}
    void zoo(EventInterface* peer);
    void shop(EventInterface* peer);
    void birthday();
};

class Strawberry: public EventInterface {
public:
    std::set<EventInterface*> visited_shop;   //这里使用set，注意去重
    Strawberry(): EventInterface() {}
    ~Strawberry() {}
    void zoo(EventInterface* peer);
    void shop(EventInterface* peer);
    void birthday();
};