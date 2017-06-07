#pragma once
#include <iostream>
#include "Object.h"
#include "math.h"
#include "allegro.h"
using namespace std;

class Bullet : public Object
{
private:
    BITMAP* image;
    int alivevar;
    int type;
    int length;
    direction state;
public:
    Bullet(BITMAP*,direction, int ,int,float,float,float,float );
    ~Bullet();
    void Move();
    void TakeDamage(int);
    void Draw(BITMAP*);
    void Save(ofstream&);
    bool onGround()
    {
        alivevar = alivevar + 1;
        if(alivevar==300)
        {
            alivevar = 0;
            setAlive(false);

            return true;
        }
        return false;
    }
    void ApplyGravity()
    {

    }
    void ChangeState(direction,int)
    {

    }

};
