#pragma once
#include"Node.h"

class Queue
{
private:
    NodeX* head;
    NodeX* tail;
    int length;
public:
    Queue();
    ~Queue();
    void Push(Data);
    void Clean();
    bool isEmpty();
    Data Pop();
//    void Render(long int& frame, SDL_Renderer* gRenderer);
//    void Move();
};
