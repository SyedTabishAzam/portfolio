#pragma once
#include"allegro.h"
#include"Object.h"
#include"Point.h"
#include"LightArmour.h"
#include"HeavyArmour.h"
enum STATE {LEFT, MIDDLE, RIGHT};
class Plane : public Object
{

protected:
    BITMAP* image;
    Point position;
    int frame_width;
    int frame_height;
    int type;
    int health;
    float velx;
    float vely;

public:
    Plane();
    Plane(BITMAP* image, int frame_width, int frame_height, Point position);
    Plane(BITMAP* image, int frame_width, int frame_height, float, float);
    virtual ~Plane();
    void Draw(BITMAP*, bool) = 0;
    virtual void SetPosition(Point*);
    virtual void SetPosition(float, float);
    Point GetPosition();
    void Move(float, float);
    void SetVelocityX(float);
    void SetVelocityY(float);
    int GetFrameWidth();
    int GetFrameHeight();
    void SetAlive(bool);
    bool Alive();
    void SetHealth(int);
    int GetHealth();
    int GetType();
    void TakeDamage(int);
};

