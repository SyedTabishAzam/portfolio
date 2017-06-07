#pragma once
#include "Shape.h"
#include <iostream>
#include "node.h"
#include "LinkedList.h"

using namespace std;

//Pretty much self explanatory, this is a doubly circular linked list


class layerStack : public LinkedList
{
private:
    Node<LinkedList*>* head;
    Node<LinkedList*>* tail;
    int cot;
public:
    layerStack();
    ~layerStack();
    void Push(LinkedList*,bool);
    void Pop();
    Node<LinkedList*>* getTail();
    void Drawall(BITMAP*);
    void moveup();

};

