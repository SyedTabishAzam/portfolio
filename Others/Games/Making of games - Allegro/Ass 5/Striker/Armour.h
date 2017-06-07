#pragma once
#include"allegro.h"
#include"Point.h"
#include<iostream>

using namespace std;

class Armour
{
protected:
    BITMAP* image;
    Point position;
    int frame_width;
    int frame_height;
    int healthAddition;
public:
    Armour();
    Armour(BITMAP* image, int frame_width, int frame_height, Point& position);
    Armour(BITMAP* image, int frame_width, int frame_height, float, float);
    virtual ~Armour();
    virtual void Draw(BITMAP*) = 0;
    void SetPosition(Point*);
    void SetPosition(float, float);
    void Move(float, float);
    virtual int GetHealthAddition() = 0;
};
