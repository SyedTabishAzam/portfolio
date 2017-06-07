#include "Tile.h"

Tile::Tile(LTexture* image, int tileType,int pos)
{
    click=false;
    img = image;
    extern LTexture hurdle;
    hurdleImg = &hurdle;
    reachable=false;
    access=true;
    occupied = false;
    this->pos = pos;
    box.x = (pos % 11) * 60;
    box.y = int(pos/11) *60;

    box.w = 60;
    box.h = 60;

    type = tileType;
    if (type==0)
    {
        setAccess(false);
    }
}

void Tile::clicked(bool didClick)
{
    click=didClick;

}

void Tile::setAccess(bool acc)
{
    access = acc;
}

bool Tile::getAccess()
{
    return access;
}

void Tile::setReachable(bool acb)
{
    reachable=acb;
}

bool Tile::getReachable()
{
    return reachable;
}

void Tile::setOccupied(bool occ)
{
    occupied = occ;
}

bool Tile::getOccupied()
{
    return occupied;
}

int Tile::getType()
{
    return type;
}

SDL_Rect Tile::getBox()
{
    return box;
}

void Tile::Render(SDL_Renderer* gRenderer)
{
    if(access)
    {

        if(reachable)
        {
            int x = box.x;
            int y = box.y;
            SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 5 );
            SDL_RenderDrawLine(gRenderer,x,y,x+60,y);
            SDL_RenderDrawLine(gRenderer,x+60,y,x+60,y+60);
            SDL_RenderDrawLine(gRenderer,x,y,x,y+60);
            SDL_RenderDrawLine(gRenderer,x,y+60,x+60,y+60);
        }
        if(click)
        {

            //SDL_SetRenderDrawColor(gRenderer,255,255,255,255);

                SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 5 );

                int x = box.x;
                int y = box.y;
                SDL_RenderDrawLine(gRenderer,x,y,x+60,y);
                SDL_RenderDrawLine(gRenderer,x+60,y,x+60,y+60);
                SDL_RenderDrawLine(gRenderer,x,y,x,y+60);
                SDL_RenderDrawLine(gRenderer,x,y+60,x+60,y+60);
                //std::cout<<pos<<std::endl;
        }

        else
        {
           // img->Render( box.x , box.y , 0, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
        }
    }
    else
    {
             hurdleImg->Render( box.x , box.y , 0, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
    }
}
