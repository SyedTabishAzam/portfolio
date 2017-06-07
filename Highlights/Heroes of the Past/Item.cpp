#include "Item.h"

Item::Item(LTexture* imagex,string name, Stats attributes,Size s)
{
    image = imagex;
    this->name = name;
    stat = attributes;
    pos = 0;
    sz = s;
}

Item::~Item()
{

}

Stats Item::GetStats()
{
    return stat;
}

string Item::GetName()
{
    return name;
}

void Item::setCoordinates(int x,int y)
{
    this->x = x;
    this->y = y;
}

void Item::Render(SDL_Renderer* gRenderer)
{
    int placeX =  x;
    int placeY =  y;
    image->Render( placeX , placeY , NULL, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
    SDL_RenderDrawLine(gRenderer,placeX,placeY,placeX+sz,placeY);
    SDL_RenderDrawLine(gRenderer,placeX+sz,placeY,placeX+sz,placeY+sz);
    SDL_RenderDrawLine(gRenderer,placeX,placeY,placeX,placeY+sz);
    SDL_RenderDrawLine(gRenderer,placeX,placeY+sz,placeX+sz,placeY+sz);
}
