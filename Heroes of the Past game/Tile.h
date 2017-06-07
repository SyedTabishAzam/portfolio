#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
class Tile
{
private:

    int type;
    SDL_Rect box;
    int pos;
    bool access;
    bool reachable;
    bool click;
    bool occupied;
    LTexture* img;
    LTexture* hurdleImg;
public:
    Tile(LTexture* image, int tileType,int pos);
    int getType();
    void setReachable(bool);
    bool getReachable();
    void clicked(bool);
    void setAccess(bool);
    bool getAccess();
    void setOccupied(bool);
    bool getOccupied();
    void Render(SDL_Renderer* gRenderer);
    SDL_Rect getBox();
};
