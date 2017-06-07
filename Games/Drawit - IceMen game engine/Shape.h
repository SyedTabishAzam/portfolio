#pragma once
#include"Point.h"
#include"allegro.h"

/** Abstract Class that defines all shapes **/

class Shape
{
protected:
    Point position;
    int type;
public:
    Shape();
    Shape(const Point&);
    virtual ~Shape();
    void SetPosition(const Point&);
    const Point& GetPosition();
    virtual const Point& GetBottomRight();
    virtual int GetRadius();
    int GetType();
    virtual void Draw(BITMAP*) = 0;
};
