#pragma once
#include "Stats.h"
#include "LTexture.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

enum Items{BOW,COIN,ENVELOPE,HEART,BELT,BIGCLUB,BOW2,CHAINBREAST,HELMET,CLAW,HALBERD,LEATHERBOOT,LCHEST,GLOVES,RING,SPEAR,SWORD,POISONBLUE,POISONGREE,DAGGR};
enum Size {SMALL=32,LARGE=64};
using namespace std;
class Item
{
    private:
        LTexture* image;
        int pos;
        float x;
        float y;
        string name;
        Stats stat;
        int sz;

    public:
        /** Default constructor */
        Item(LTexture* image,string,Stats,Size);
        /** Default destructor */
        ~Item();
        void setCoordinates(int x,int y);
        void Render(SDL_Renderer* gRenderer);
        bool GetAlive()
        {
            return true;
        }
        Stats GetStats();
        string GetName();

};


