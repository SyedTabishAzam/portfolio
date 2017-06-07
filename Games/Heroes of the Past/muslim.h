#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "list.cpp"
#include "LTexture.h"
#include "vector"
#include <algorithm>
#include "Item.h"
#include "Stats.h"
#include "Unit.h"

class muslim: public Unit
{

public:
    muslim(LTexture* sheet,LTexture* inventoryImage,TTF_Font *gFont,int pos,MOTION);
    ~muslim();
    void Render( SDL_Renderer* gRenderer,int);
};
