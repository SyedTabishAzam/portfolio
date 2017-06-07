#pragma once
#include "Object.h"
#include "allegro.h"
#include "fstream"
#include "sstream"
#include "Hurdles.h"
#include "FlameThrower.h"
#include "vector"


class Map
{
private:
    BITMAP* image;
    int level;

public:
    Map();
    ~Map();
    void GetSpecs(vector<Object*>&,vector<Object*>&,BITMAP*);
    void ChangeLevel();
};
