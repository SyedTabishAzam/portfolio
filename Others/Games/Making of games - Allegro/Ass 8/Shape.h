#pragma once
#include"Point.h"
#include <iostream>
#include"Color.h"
#include"allegro.h"

using namespace std;
/** Abstract Class that defines all shapes **/

class Shape
{
protected:
    Color color;
    Point position;
    string type;
public:
    bool alive;
    Shape();
    string GetType();
    virtual int GetRadius();
    Shape(const Point&, const Color&);
    virtual ~Shape();
    virtual const Point& GetBottomRight();
    void SetColor(const Color&);
    int GetColor();
    virtual Point GetPosition();
    void SetPosition(const Point&);
    virtual void CPosition(int);
    virtual void Draw(BITMAP*) = 0;
    virtual int GetLength();
    virtual int GetBreadth();
};
