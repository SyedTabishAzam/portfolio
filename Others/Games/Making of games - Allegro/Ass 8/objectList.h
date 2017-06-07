#pragma once
#include "Shape.h"
#include <iostream>
#include "node.h"
#include "LinkedList.h"
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

//Pretty much self explanatory, this is a doubly circular linked list


class objectList : public LinkedList
{
private:
    Node<Shape*>* head;
    Node<Shape*>* tail;
public:
    objectList();
    ~objectList();
    void moveup();
    void movedown();
    void Drawall(BITMAP*);
    void Swap();
    void WriteFile();

};

