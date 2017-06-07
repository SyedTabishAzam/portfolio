#pragma once
#include<iostream>
#include"allegro.h"
#include"Object.h"
#include "Explosion.h"
#include "Powerups.h"
#include "Plane.h"
#include "Player.h"
struct Node
{
    Object* object;
    Node* next;
    Node* prev;
    ~Node()
    {
        std::cout<<"Node Deleted"<<endl;
        delete object;
        object = NULL;

    }
};

class LinkedList
{
private:
    int length;
    Node* head;
    Node* tail;
public:
    LinkedList();
    ~LinkedList();
    void Append(Object*);
    void InsertAt(Object*, int);
    Object* DeleteAt(int);
    Object* Pop();
    void CleanAll();
    void CheckCollision(BITMAP*,Player*);
    void Collide(Object*,Object*,BITMAP*);
    int Length();
    void MoveAll();
    bool hit(Object*,Object*);
    Node* GetHead();
    void DrawAll(BITMAP*, bool);
};

