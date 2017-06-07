#pragma once
#include <iostream>
#include "allegro.h"
using namespace std;

class BackgroundGame
{
private:
    BITMAP* image;
    float x;
    float y;
public:
    BackgroundGame(BITMAP*,float,float);
    ~BackgroundGame();
    void Draw(BITMAP*);

};
