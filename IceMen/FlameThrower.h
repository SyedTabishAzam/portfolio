#pragma once
#include "Enemy.h"
#include "allegro.h"
#include <iostream>
#include <fstream>
using namespace std;

class FlameThrower : public Enemy
{
private:
    int walkstate;
public:
    FlameThrower(BITMAP*,float,float,float,float);
    ~FlameThrower();
    void Draw(BITMAP* buffer);
    void ChangeState();
    void Save(ofstream&);
    void Load(ifstream&);
};
