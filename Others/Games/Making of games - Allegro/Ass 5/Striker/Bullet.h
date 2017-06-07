#pragma once
#include"Plane.h"

class Bullet : public Plane
{
public:
    Bullet(BITMAP* image, int frame_width, int frame_height, Point position);
    Bullet(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Bullet();
    void Move();
    void Move(float, float);
    void Draw(BITMAP*, bool);
};

