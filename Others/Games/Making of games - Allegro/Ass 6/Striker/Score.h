#pragma once
#include "iostream"
#include "Writer.h"
#include "Object.h"
#include "allegro.h"

//Class to maintain the scores for different enemies deaths
class Score
{
private:
    BITMAP* image;
    int positionx;
    int positiony;
    int sc;
public:
    Score(BITMAP*,int,int);
    ~Score();
    void AddGlobal(int);
    void Determine(int);
    void Globe(int points);
    void Draw(BITMAP*);

};
