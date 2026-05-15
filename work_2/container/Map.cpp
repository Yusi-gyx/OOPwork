#pragma once
#include"Map.h"
#include"Pair.h"

Map::Map(int n)
{
    data = new Pair[n] ;
    sz = 0 ;
}
Map::~Map()
{
    delete[] data ;
}

int Map::size() const
{
    return sz ;
}

int & Map::operator [](const string & k)
{
    for(int i = 0 ; i < sz ; i ++)
    {
        if(data [i].hasKey(k))
        {
            return data[i].getVal() ;
        }
    }
    data [sz].reset(k, 0);
    sz ++ ;
    return data [sz - 1].getVal() ;
}

int Map::operator [](const string & k) const
{
    for(int i = 0 ; i < sz ; i ++)
    {
        if(data [i].hasKey(k))
        {
            return data[i].getVal();
        }
    }
    return 0 ;
}