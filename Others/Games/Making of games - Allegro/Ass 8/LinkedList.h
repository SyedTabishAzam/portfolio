#pragma once
#include "Shape.h"
#include <iostream>
#include "node.h"

using namespace std;

//Pretty much self explanatory, this is a doubly circular linked list


class LinkedList
{
private:
    Node<Shape*>* head;
    Node<Shape*>* tail;
    int leng;
public:
    LinkedList();
    int GetLength();
    virtual void WriteFile();
    ~LinkedList();
    void Push(Shape*,bool);
    void Pop();

    Node<Shape*>* getTail();
    Node<Shape*>* getHead();

    void moveup();

    void Drawall(BITMAP*);
    bool isEmpty();
};
