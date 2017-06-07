#pragma once
#include "Plane.h"
#include "allegro.h"
#include <iostream>

using namespace std;
//Explosion class, works similar to bullet class
class Explosion : public Plane
{
private:
    int sp;
    SAMPLE* explodeSound;

public:
    Explosion(BITMAP* image, int frame_width, int frame_height, Point position);
    Explosion(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Explosion();
    void Move();
    void Draw(BITMAP*,bool);
};
