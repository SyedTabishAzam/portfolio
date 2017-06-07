#pragma once
#include"Plane.h"
#include"Armour.h"
#include "HealthBar.h"
enum {LIGHT = 2, HEAVY = 3,YELLOW = 1};

class Player : public Plane
{
private:
    int maxHealth;
    Armour* armour;
    int currentArmour,bullettype;
    HealthBar* healthbar;
    int yellcount;
    SAMPLE* pupSound;
public:
    Player(BITMAP* image, int frame_width, int frame_height, Point position);
    Player(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Player();
    void Draw(BITMAP* , bool );
    void CreateArmour(int);
    void ChangeBullet(int);
    void UsePuP(int);
    void SetPosition(Point* position);
    void SetPosition(float, float);
    void SetVelocityX(float);
    void SetVelocityY(float);
    void Move();
    void Move(Object*);
    void Move(float, float);
    Object* Fire();
};
