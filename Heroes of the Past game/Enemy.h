#pragma once

#include"Unit.h"

class Enemy:public Unit
{
public:
    Enemy(LTexture* image,int pos);
    Enemy();
    virtual ~Enemy();
    virtual void Move();
    virtual void Render(long int& frame, SDL_Renderer* gRenderer);
};
