#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "list.cpp"
#include "LTexture.h"
#include "vector"
#include <algorithm>
#include "Item.h"
#include "Stats.h"
#include "Inventory.h"
using namespace std;


enum MOTION {RIGHT, LEFT, UP, DOWN};
enum STATE {IDLE,WALK,HURT,ATTACK,DEAD};


class Unit
{
    protected:
        bool alive;
        float x;
        float y;
        int pos;
        bool focus;
        float speedx;
        float speedy;
        Stats stat;
        int width[5] = {71.12,73.5,72,112,107.5};
        int height[5];
        float friction; //lower speed means more friction
        Inventory* invent;
        enum ANIMATION_FRAMES {FRAMES = 8};

        int state = IDLE;
        SDL_Rect spriteClips[5][ FRAMES ];
        SDL_Rect box;
        int direction;
        vector<int> open;
        LTexture* SpriteSheets;

        TTF_Font *gFont;
        LTexture gTextTexture;
        bool pauseframe;

    public:
        Unit(LTexture* sheet,LTexture* inventoryImage,TTF_Font *gFont,int pos,MOTION dr);
        Unit();
        int getPosition();
        virtual ~Unit();
        void SetAlive(bool);
        int GetState();
        void SetState(int);
        bool GetAlive();
        void SetFocus(bool);
        bool GetFocus();
        int getType();
        void getHurt(float damage);
        int GetMotion();
        void SetMotion(int);
        int getSpeed();
        int getDamage();
        void addItem(Item*);
        Item* getItem();
        bool animationComplete;
        float getY();
        float getX();
        SDL_Rect getBox();
        void Move(int dest);
        void Move();
        void drawText(string text,int,int,SDL_Renderer* gRenderer);
        virtual void showInventory( SDL_Renderer* gRenderer);
        vector<int> showReachable();
        void showStats( SDL_Renderer* gRenderer);
        virtual void Render( SDL_Renderer* gRenderer,int);
        virtual vector<int> showEssential(SDL_Renderer*);
};



