#pragma once

#include <iostream>
#include "allegro.h"
#include "string"
//Class created to draw text on the screen
using namespace std;
class Writer
{
private:
    BITMAP* image;
    int startx, starty;
    int startrow,widthandheight;
    bool smfont;
    string text;
public:
    Writer(BITMAP*,string,bool,int,int);
    void Draw(BITMAP*);
};
