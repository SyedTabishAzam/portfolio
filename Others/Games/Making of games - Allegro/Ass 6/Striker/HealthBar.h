#pragma once
#include"allegro.h"
#include"Point.h"
#include "Writer.h"
class HealthBar
{
private:
    Point position;
    BITMAP* image;
    float healthfactor;
public:
    HealthBar(BITMAP*, float x, float y);
    ~HealthBar();
    void Move(float playerhp,int maxhealth);
    void Draw(BITMAP*);
};
