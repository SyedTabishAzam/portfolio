#pragma once
#include "Shape.h"

template <typename T>
struct Node
{
    T object;
    Node* next;
    Node* prev;
};
