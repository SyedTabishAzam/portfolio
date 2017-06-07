#pragma once
#include "Object.h"

class Powerup: public Object
{
private:
    int duration;
    BITMAP* image;
public:
    Powerup(BITMAP*,float,float,float,float);
    ~Powerup();
    void Move();
    int DeterminePup();
    void Draw(BITMAP*);
    void Save(ofstream&);
};
