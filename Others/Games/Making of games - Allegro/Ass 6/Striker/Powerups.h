#pragma once
#include "allegro.h"
#include "Point.h"
#include "Plane.h"

class Powerups : public Plane
{
private:
    BITMAP* image;
    Point pos;
    int powerup;
public:
    Powerups(BITMAP*,int,Point);
    ~Powerups();
    void Draw(BITMAP*,bool);
    void Move();
};
