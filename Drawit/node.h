#pragma once
#include"Shape.h"

struct Node
{
    Shape* shape;
    Node* next;
    Node* prev;
};
