#pragma once
#include "allegro.h"
#include "Object.h"
#include "vector"

class Hurdles : public Object
{
private:
    float width;
    float height;
public:
    Hurdles(BITMAP*,float,float,float,float);
    ~Hurdles();
    void Draw(BITMAP*);
    void Move();
    void Save(ofstream&);
    void Load(ifstream&);
};

