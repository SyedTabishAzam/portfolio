#pragma once
#include"allegro.h"
#include<iostream>
using namespace std;

enum {PIXEL=1, RECT=2};
/** Template node structure for creating Doubly linked list **/
template <typename Type>
struct Node
{
    Type* data;
    Node* next;
    Node* prev;
};

/** Template class for Doubly Linked List **/
template <typename Type>
class LinkedList
{
    private:
        Node<Type>* head;
        Node<Type>* tail;
        int lengthH;
        int lengthE;
        int length;
    public:
        LinkedList();
        ~LinkedList();
        void Insert(Type*);
        void Remove();
        void Push(Type*);
        void Pop();
        void Draw(BITMAP*);
        void WriteFile();
        int GetLengthH();
        int GetLengthE();
        bool IsEmpty();
};

/** Constructor **/
template <typename Type>
LinkedList<Type>::LinkedList()
{
    this->head = NULL;
    lengthH = 0;
    lengthE=0;
    length=0;
}

/** Destructor **/
template <typename Type>
LinkedList<Type>::~LinkedList()
{
    if(head!=NULL)  //Do nothing if list is empty
    {
        Node<Type>* temp = head;
        tail->next = NULL;  //This helps in stopping the while loop

        while(temp!=NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

}

/** Grows the tail of the Linked List **/
template <typename Type>
void LinkedList<Type>::Insert(Type* data)
{
    Node<Type>* temp = new Node<Type>;
    temp->data = data;
    if(data->GetType()==1)
    {
        lengthE++;
    }
    if(data->GetType()==2)
    {
        lengthH++;
    }
    if(head == NULL)    //If linked list is empty, let head hold the data in a single node
    {
        head = temp;
        tail = temp;
        temp->next = head;
        temp->prev = head;
    }
    else                //increase the tail
    {
        tail->next = temp;
        temp->prev = tail;
        temp->next = head;
        tail = temp;
        head->prev = tail;
    }
    length++;

}

/** Shortens the tail of the linked list **/
template <typename Type>
void LinkedList<Type>::Remove()
{
    if(tail->data->GetType()==1)
    {
        lengthE--;
    }
    if(tail->data->GetType()==2)
    {
        lengthH--;
    }
    if(tail == head)    //If there is only one Node in the linked list, delete it
    {
        delete tail;
        head = NULL;
        tail = NULL;
    }
    else
    {
        Node<Type>* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }
    length--;
}

/** increases the head of the linked list **/
template <typename Type>
void LinkedList<Type>::Push(Type* data)
{
    Node<Type>* temp = new Node<Type>;
    temp->data = data;
    if(data->GetType()==1)
    {
        lengthE++;
    }
    if(data->GetType()==2)
    {
        lengthH++;
    }
    if(head == NULL)    //If linked list is empty, let head hold the data in a single node
    {
        head = temp;
        tail = temp;
        temp->next = head;
        temp->prev = head;
    }
    else                //increase the head
    {
        temp->next = head;
        temp->prev = tail;
        tail->next = temp;
        head = temp;
    }
    length++;
}

/** Shortens the head of the linked list **/
template <typename Type>
void LinkedList<Type>::Pop()
{
    if(tail == head)    //If there is only one Node in the linked list, delete it
    {
        delete tail;
        head = NULL;
        tail = NULL;
    }
    else
    {
        Node<Type>* temp = head;
        head = head->next;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }
    length--;
}

/** Draws all the objects in the linked list **/
template <typename Type>
void LinkedList<Type>::Draw(BITMAP* buffer)
{
    if(IsEmpty() == false)
    {
        Node<Type>* temp = head;
        for(int i=0;i<length;i++)
        {
            temp->data->Draw(buffer);
            temp = temp->next;
        }
    }
}

/** returns true if the linked list is empty, false otherwise **/
template <typename Type>
bool LinkedList<Type>::IsEmpty()
{
    if(this->head == NULL)
        return true;
    return false;
}

/** returns the length of the linked list **/
template <typename Type>
int LinkedList<Type>::GetLengthH()
{
    return lengthH;
}

template <typename Type>
int LinkedList<Type>::GetLengthE()
{
    return lengthE;
}

/** returns the length of the linked list **/
template <typename Type>
void LinkedList<Type>::WriteFile()
{
    const char *path="C:/Users/Tabish/db/Dropbox/Project/IceMen/level1.txt";
    ofstream htmlFile;
    htmlFile.open (path);  //Name of the HTML file to be created

    //*********** Draw Figures Here ************
    if(IsEmpty() == false)
    {
        Node<Type>* temp = head;
        htmlFile<<GetLengthH()<<endl;
        for(int i = 0; i<length; i++)
        {
            int type = temp->data->GetType();
            if(type==RECT)
            {
                cout<<"writing hurdle"<<endl;
                htmlFile<<temp->data->GetPosition().x<<" "<<temp->data->GetPosition().y<<endl;
                htmlFile<<(temp->data->GetBottomRight().x)-(temp->data->GetPosition().x)<<" "<<(temp->data->GetBottomRight().y)-(temp->data->GetPosition().y)<<endl;

            }
            temp = temp->next;
        }

        temp = head;
        htmlFile<<GetLengthE()<<endl;
        for(int j = 0; j<length; j++)
        {

            int type = temp->data->GetType();
            cout<<type<<" enemy"<<endl;
            if(type==PIXEL)
            {
                cout<<"writing enemy"<<endl;
                htmlFile<<"11 "<<temp->data->GetPosition().x<<" "<<temp->data->GetPosition().y<<endl;
            }
            temp = temp->next;
        }
    }
    //******************************************

	htmlFile.close();   //Closing the HTML file
}
