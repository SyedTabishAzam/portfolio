#pragma once
#include"Unit.h"

struct NodeX
{
    Unit* unit;
    NodeX* next;
    NodeX* prev;

    ~NodeX()
    {
        delete unit;
    }
};


struct Data
{
    int pos;
    int cost;
    bool operator<( const Data & n ) const
    {
    return this->pos < n.pos;   // for example
    }


};
