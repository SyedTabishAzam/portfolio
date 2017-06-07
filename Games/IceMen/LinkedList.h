#pragma once
#include "SnowMan.h"
#include "Enemy.h"
#include "FlameThrower.h"
#include "Hurdles.h"
#include <fstream>
template <typename T>
struct Node
{
    Node<T>* prev;
    Node<T>* next;
    T data;
    ~Node<T>()
    {
        delete data;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int length;
public:
    LinkedList()
    {
        cout<<"Linked List Created"<<endl;
        head=NULL;
        tail=NULL;
        length=0;
    }
    ~LinkedList()
    {
        cout<<"Linked List Destroyed";
        CleanAll();
        delete head;
        delete tail;
        head = NULL;
        tail = NULL;
    }
    void Save();
    void Load();
    void Push(T data);
    T Pop();
    bool isEmpty();
    void Draw(BITMAP* buffer);
    void Update();
    void CleanAll();
    void Move();
    void CheckCollision();
    void Collide(Object*,Object*);
    bool hit(Object*,Object*);
    int GetLength();
};
