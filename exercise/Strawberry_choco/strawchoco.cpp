#include "strawchoco.h"
#include "event.h"

void Chocolate::zoo(EventInterface* peer)
{
    increase_mood(5);
    visited_zoo.push_back(peer);
} 

void Chocolate::shop(EventInterface* peer)
{
    increase_mood(1);
}

void Chocolate::birthday()
{
    increase_mood(1);
    int n = visited_zoo.size();
    if(n)
    {
        increase_mood(5);
        visited_zoo [n - 1]->increase_mood(1);
    }
}

void Strawberry::zoo(EventInterface* peer)
{
    increase_mood(1);
    if(dynamic_cast<Chocolate*>(peer)) //同伴是巧克力
    {
        increase_mood(5);
    }
}

void Strawberry::shop(EventInterface* peer)
{
    increase_mood(5);
    visited_shop.insert(peer);
    if(dynamic_cast<Chocolate*>(peer)) //同伴是巧克力
    {
        increase_mood(5);
    }
}

void Strawberry::birthday()
{
    int n = visited_shop.size();
    increase_mood(n);
    if(n)
    {
        for(auto x: visited_shop)
        {
            x->increase_mood(1);
        }
    }
}