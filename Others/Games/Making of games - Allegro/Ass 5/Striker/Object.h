#pragma once
#include"Point.h"
#include"allegro.h"
#include <iostream>

using namespace std;


class Object
{
protected:
    BITMAP* image;
    bool alive;
public:
    bool Alive()
    {
        return alive;
    }
    void SetAlive(bool alive)
    {
        this->alive = alive;
    }
    virtual ~Object()
    {
       // cout<<"Object Deleted"<<endl;
    }
    virtual void SetVelocityX(float) = 0;
    virtual void SetVelocityY(float) = 0;
    virtual void Move() = 0;
    virtual void Draw(BITMAP*, bool) = 0;
    virtual int GetFrameWidth() = 0;
    virtual int GetFrameHeight() = 0;
    virtual Point GetPosition() = 0;
    virtual void SetHealth(int) = 0;
    virtual int GetHealth() = 0;
    virtual int GetType() = 0;
    virtual void TakeDamage(int)=0;
};

