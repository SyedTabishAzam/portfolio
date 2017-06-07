#pragma once
#include "Shape.h"
#include <iostream>
#include "node.h"
#include "LinkedList.h"

using namespace std;

//Pretty much self explanatory, this is a doubly circular linked list


class historystack : public LinkedList
{
private:
    Node<Shape*>* head;
    Node<Shape*>* tail;
public:
    historystack();
    ~historystack();
    void Push(Shape*,bool);
    Node<Shape*>* getTail();
    void Pop();
    bool isEmpty();
};
