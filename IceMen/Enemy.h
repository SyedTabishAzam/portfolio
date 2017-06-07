#pragma once
#include "allegro.h"
#include "Object.h"
#include "Powerup.h"
#include <iostream>
#include <fstream>
using namespace std;


class Enemy : public Object
{
private:
    int stepper;
    int ballhealth;
    int ran;
    int dfact;
    bool stepcomplete;
protected:
    BITMAP* image;
    int direction;
    ICESTATE iceball;
public:
    Enemy();
    ~Enemy();
    virtual void Draw(BITMAP*)=0;
    void Move();
    void ChangeState(int,int);
    virtual void ChangeState()=0;
    int GetState();
    void TakeDamage(int);
    virtual void Save(ofstream&){};
    virtual void Save(ifstream&){};
    Object* InstantDeath();
};
