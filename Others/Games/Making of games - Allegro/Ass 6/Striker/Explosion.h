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
    bool setalive;
    int ck;
    Score* counter;
public:
    Explosion(BITMAP* image, int frame_width, int checker,int frame_height, int x, int y);
    ~Explosion();
    void Move();
    void Draw(BITMAP*,bool);

};
