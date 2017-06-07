#pragma once
#include <iostream>
#include "allegro.h"
#include "Object.h"
#include "Bullet.h"

using namespace std;

enum {BLUE = 15, RED = 17,YELLOW = 16};
class SnowMan : public Object
{
private:
    BITMAP* image;
    int speed;
    int walkstate;
    bool triggered;
    float jumpvar;
    direction state;
    int bullettype,bulletlength;
    direction facingstate;
    float gamespeed;
    int chance;
public:
    SnowMan(BITMAP*,float,float,float,float);
    ~SnowMan();
    void TakeDamage(int);
    void ChangeState(direction,int);
    int GetState();
    void ResetPosition();
    void UsePup(int);
    void ChangeAttrib(int,int,int);
    int getSpeed();
    void setSpeed(int);
    void Draw(BITMAP*);
    void Move();
    Object* Fire();
    void Save(ofstream&);
    void Load(ifstream&);
};
