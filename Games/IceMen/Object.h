#pragma once
#include <iostream>
#include "allegro.h"
#include "vector"
#include <typeinfo>
#include "sstream"
#include <fstream>

using namespace std;
enum direction{LEFT,RIGHT,JUMP,FREE};
enum ICESTATE{NORMAL,HOT,MELT,WARM,COLD,BALL,BALLMOVE=6};
class Object
{
protected:

    float x;
    float y;
    int damage;
    float positionX, positionY;     // Position of the character
    float velocityX, velocityY;     // Velocity of the character
    float frame_width;
    float frame_height;
    int type;
    int health;
    BITMAP* image;
    vector<Object*> gr;
private:
    bool alive;
public:

    bool isAlive()
    {
        return alive;
    }
    int GetType()
    {
        return type;
    }
    void setAlive(bool aliv)
    {
        this->alive=aliv;
    }
    virtual ~Object()
    {
        cout<<"destroyed"<<endl;
    }
    virtual void Move()=0;
    virtual void Draw(BITMAP*) = 0;
    virtual bool onGround()
    {

        vector<Object*>::iterator it;
        vector<Object*> obstacs;
        obstacs=GetGrounds();
        for(it = obstacs.begin();it!=obstacs.end();it++)
        {
            if(Hit(this,*it)==true)
                return true;
        }
        return false;
    }
    virtual void ApplyGravity()
    {
        if(onGround()==false)
        {

            ChangePosition(x,y+1);
        }
    }
    virtual bool CheckWalls(string checkfor)
    {

        vector<Object*>::iterator it;
        vector<Object*> obstacs;
        obstacs=GetGrounds();
        for(it = obstacs.begin();it!=obstacs.end();it++)
        {
            if(WallHit(this,*it,checkfor)==true)
                return true;
        }
        return false;




    }
    void SetGrounds(vector<Object*> obstacs)
    {
        gr = obstacs;
    }

    vector<Object*> GetGrounds()
    {
        return gr;
    }

    float GetX()
    {
        return x;
    }

    float GetY()
    {
        return y;
    }
    float GetFrameWidth()
    {
        return frame_width;
    }
    float GetFrameHeight()
    {
        return frame_height;
    }
    virtual void ChangePosition(float x,float y)
    {
        float prevx = this->x;
        float prevy = this->y;
        this->x=x;
        this->y=y;
        if(CheckWalls("x"))
        {
            this->x=prevx;
        }
        if(CheckWalls("y"))
        {
            this->y=prevy;
        }



    }
    bool Hit(Object* object1, Object* object2)
    {
        int left1, left2;
        int right1, right2;
        int  top2;
        int bottom1;
        left1 = object1->GetX();       //left 1 is object 1's x coord
        left2 = object2->GetX();       //left 2 is object 2's x coord
        right1 = object1->GetX() + object1->GetFrameWidth();   //right 1 is objects 1's x + frame width, that makes it top right coord
        right2 = object2->GetX() + object2->GetFrameWidth();   //right 2 is object 2's top right coord


        top2 = object2->GetY();    //object 2's y
        bottom1 = object1->GetY() + object1->GetFrameHeight(); //object 1's bottom left


        if (bottom1 == top2  && right1 > left2 && left1<right2 )
        {

            return true;  //if object 1's bottom left is lesser than object 2's top left (not touching)
        }

        return false;   //if these conditions are not met, then it is definately colliding
    }

    bool WallHit(Object* object1, Object* object2,string checkfor)
    {
        float left1, left2;
        float right1, right2;
        float top1, top2;
        float bottom1, bottom2;
        left1 = object1->GetX();       //left 1 is object 1's x coord
        left2 = object2->GetX();       //left 2 is object 2's x coord
        right1 = object1->GetX() + object1->GetFrameWidth();   //right 1 is objects 1's x + frame width, that makes it top right coord
        right2 = object2->GetX() + object2->GetFrameWidth();   //right 2 is object 2's top right coord

        top1 = object1->GetY();    //object 1's y
        top2 = object2->GetY();    //object 2's y
        bottom1 = object1->GetY() + object1->GetFrameHeight(); //object 1's bottom left
        bottom2 = object2->GetY() + object2->GetFrameHeight(); //object 2's bottom left
        if(checkfor=="x")
        {

            if (right1 > left2 && left1 < right2 && top1 < bottom2 && bottom1>top2 )
            {

                return true;  //if object 1's bottom left is lesser than object 2's top left (not touching)
            }

            return false;   //if these conditions are not met, then it is definately colliding
        }
        if(checkfor=="y")
        {

            if (bottom1 > top2 && top1<bottom2 && left1<right2 && right1>left2 )
            {

                return true;  //if object 1's bottom left is lesser than object 2's top left (not touching)
            }

            return false;   //if these conditions are not met, then it is definately colliding
        }
        return false;
    }
    int GetHealth()
    {
        return health;
    }
    virtual Object* InstantDeath(){ return this;};
    virtual void UsePup(int){}
    virtual void ChangeState(int,int){}
    virtual int GetState(){ return 0;}
    int GiveDamage()
    {
        return damage;
    }
    virtual void TakeDamage(int){}
    virtual void Save(ofstream&){};
    virtual void Load(ifstream&){};
    //virtual Object* Fire(){}
};
