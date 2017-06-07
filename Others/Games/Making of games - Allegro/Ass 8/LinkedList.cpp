#include "LinkedList.h"




LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
    leng = 0;

}

LinkedList::~LinkedList()
{
    cout<<"LinkedList Destroyed"<<endl;
}

int LinkedList::GetLength()
{
    return leng;
}
void LinkedList::Drawall(BITMAP* buffer)
{ //if the list isnt empty, draw every node's object
    if(!isEmpty())
    {
        Node<Shape*>* temp = head;
        temp->object->Draw(buffer);
        temp = temp->next;
        while(temp != head)
        {
            if(temp->object->alive) //this checks if whether the object is alive or not (not alive means its in the list but not has to be drawn)
                temp->object->Draw(buffer);
            temp = temp->next;
        }
    }

}

void LinkedList::Push(Shape* item,bool delStack)
{

    leng++;
    if(head==NULL)
    {   //Pushing according to the algorithm
        Node<Shape*>* temp = new Node<Shape*>;

        temp->object = item;
        head = temp;
        head->prev = head;
        tail = temp;

        head->next = tail;
    }
    else
    {
        Node<Shape*>* temp = new Node<Shape*>;
        temp->object = item;
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        head->prev = temp;
        tail = temp;
    }
}

Node<Shape*>* LinkedList::getTail()
{
    return tail;
}

Node<Shape*>* LinkedList::getHead()
{
    return head;
}

void LinkedList::Pop()
{
    leng--;
    if(tail==head)
    {

        delete tail;
        tail = NULL;
        head = NULL;

    }
    else
    {
        Node<Shape*>* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
        temp = NULL;

    }
}






void LinkedList::moveup()
{   //calles the function Change Position (Cposition) of shape

}

bool LinkedList::isEmpty()
{   //tells if the list is empty
    return (head==NULL);
}

void LinkedList::WriteFile()
{

}


