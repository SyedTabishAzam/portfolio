#include "layerStack.h"




layerStack::layerStack()
{
    head = NULL;
    tail = NULL;
    cot = 0;

}

layerStack::~layerStack()
{
    cout<<"layerStack Destroyed"<<endl;
}

void layerStack::Drawall(BITMAP* buffer)
{ //if the list isnt empty, draw every node's object


        Node<LinkedList*>* temp = head;
        temp->object->Drawall(buffer);
        temp = temp->next;
        while(temp != head)
        {
            temp->object->Drawall(buffer);
            temp = temp->next;
        }


}

void layerStack::Push(LinkedList* item,bool delStack)
{

    cout<<"Layer "<<cot<<" created"<<endl;
    cot++;
    if(head==NULL)
    {   //Pushing according to the algorithm
        Node<LinkedList*>* temp = new Node<LinkedList*>;
        temp->object = item;
        head = temp;
        head->prev = head;
        tail = temp;
        head->next = tail;
    }
    else
    {
        Node<LinkedList*>* temp = new Node<LinkedList*>;
        temp->object = item;
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        head->prev = temp;
        tail = temp;
    }
}

Node<LinkedList*>* layerStack::getTail()
{
    return tail;
}
void layerStack::Pop()
{
    cout<<"Layer "<<cot<<" Destroyed"<<endl;
    cot--;
    if(tail==head)
    {

        delete tail;
        tail = NULL;
        head = NULL;

    }
    else
    {
        Node<LinkedList*>* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
        temp = NULL;

    }
}





