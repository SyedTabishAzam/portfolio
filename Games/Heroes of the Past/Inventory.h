#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Item.h"
#include "Stats.h"
#include "list.cpp"


using namespace std;

class Inventory
{
    public:

        void Rendeer(SDL_Renderer* gRenderer);
        Stats getStat();
        friend class Unit;

    private:
        Inventory(LTexture* inventoryImage);
        ~Inventory();
        LTexture* Image;
        void addItem(Item*);
        int counter;
        LTexture gTextTexture;
        Item* getItem();
        float x;
        float y;
        bool occupied[10] = {false};
        void addToSpecial(Item*&);
        void Render(SDL_Renderer* gRenderer);
        void showStats(SDL_Renderer* gRenderer);
        void drawText(string text,int x,int y, SDL_Renderer* gRenderer);
        DoubleLinkedList<Item*> items;

};
