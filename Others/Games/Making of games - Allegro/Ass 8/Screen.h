#pragma once
#include <iostream>
#include "allegro.h"
#include "Color.h"

using namespace std;
class Screen
{
private:
    float startx;
    float starty;
    int box;
    BITMAP* im1;
    BITMAP* im2;
    BITMAP* im3;
    BITMAP* im4;
public:
    Screen(BITMAP*,BITMAP*,BITMAP*,BITMAP*,float,float);
    ~Screen();
    Color pixColor(BITMAP*, int,int);
    bool Occupied(float x,float y);
    void BoxColors(BITMAP*);
    void Draw(BITMAP*);
    int ClickedBox(bool,float x,float y);

};
