#pragma once
#include"Plane.h"


class Bullet : public Plane
{
private:
    int targetx,targety;
    int smokecount;
public:
    Bullet(BITMAP* image, int frame_width, int typ , int frame_height, Point position,int targetx=0,int targety=0);
    Bullet(BITMAP* image, int frame_width, int typ , int frame_height, int x, int y,int targetx=0,int targety=0);
    ~Bullet();
    void Move();
    void Move(float, float);
    void Draw(BITMAP*, bool);

};

