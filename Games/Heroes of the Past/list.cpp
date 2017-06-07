#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Stats.h"
using namespace std;

template <typename T>
struct Node
{   //Doubly linked list node (data , prev pointer, next pointer)
    T data;
    Node* next;
    Node* prev;
};

template <typename T>
class DoubleLinkedList
{
private:
    Node<T>* head;  //Whenever you use a template, you need to specify for which data type
    Node<T>* tail;
    int length;
public:
    DoubleLinkedList()
    {   //initialize and keep pointers NULL
        head = NULL;
        tail = NULL;
        length=0;
    }

    ~DoubleLinkedList()
    {
        Node<T>* temp;
        temp = head;    //temp is head
        while (temp!=NULL)  //while we dont reach last node
        {
            //delete temp->data;
            temp = temp->next;
        }
        delete head;
        delete tail;
        cout<<"Double Linked List Deleted"<<endl;

    }
    void Push(T data)
    {
        if(head == NULL)
        {   //if pointers are null
            Node<T>* temp = new Node<T>;    //create a new node temp
            temp->data = data;  //save data to it
            temp->next = NULL;  //set its next to null
            temp->prev = NULL;  //set its prev to null
            tail = temp;    // set head and tail as this node
            head = temp;

            length++;
        }
        else
        {   //if head not null, means not first node
            Node<T>* temp = new Node<T>;    //create new node
            temp->data = data;  //set its data
            tail->next = temp;  //set the tail's next to this node
            temp->next = NULL;  //set this node's next to NULL
            temp->prev = tail;  //set this node's prev to the tail
            tail = temp;    //set tail as this node

            length++;
        }

    }

    T getUnitByPos(int pos)
    {

        Node<T>* temp;
        temp = head;    //temp is head
        while (temp!=NULL)  //while we dont reach last node
        {

            if (temp->data->getPosition()==pos)
                return temp->data;
            temp = temp->next;
        }

        return NULL;
    }

    T Pop()
    {

        if(!isEmpty())
        {   //if not empty, then only pop
            if(head == tail)    //if head and tail are both equal (only one node)
            {
                T x = tail->data;   //create new template type and store data in it
                delete tail;    //delete the tail
                tail = NULL;    //mark tail NULL
                head = NULL;    //mark head NULL
                length--;
                return x;   //return the stored data
            }
            else
            {   //if not the last node
                Node<T>* temp = new Node<T>;    //create new temp node
                temp = tail;    //set temp to tail
                tail = tail->prev;  //set tail as the previous of tail
                tail->next = NULL;  //set the next of the current tail as NULL
                T x = temp->data;   //save the data in the TO-BE-REMOVED node
                length--;
                return x;
            }
        }
        else
        {
            T x;        //if empty, then return garbage
            return x;
        }

    }

    bool isEmpty()
    {
        return (head==NULL);    //if head is NULL, its empty
    }

    void DisplayFirstToLast()
    {
        Node<T>* temp;
        temp = head;    //temp is head
        while (temp!=NULL)  //while we dont reach last node
        {
            cout<<temp->data<<endl; //output every data
            temp = temp->next;
        }
    }

    T ElementAt(int x)
    {

        Node<T>* temp;
        temp = head;    //temp is head
        int counter = 0;
        while (temp!=NULL)  //while we dont reach last node
        {

            if (x==counter)
            {

                return temp->data;
            }

            temp = temp->next;
            counter++;
        }
        return NULL;
    }

    int GetLength()
    {
        return length;
    }

    bool Find(T element)
    {
        bool result=false;
        Node<T>* temp;
        temp = head;    //temp is head
        while (temp!=NULL)  //while we dont reach last node
        {
            if (temp->data==element)
            {

                result = true;
                break;
            }
            temp = temp->next;
        }
        return result;
    }

    void DisplayLastToFirst()
    {
        Node<T>* temp;
        temp = tail;    //set temp as tail
        while (temp!=NULL)  //while temp doesnt reaches NULL (we know head prev is NULL)
        {
            cout<<temp->data<<endl; //output every data
            temp = temp->prev;
        }
    }

    void RenderAll(SDL_Renderer* gRenderer)
    {
        Node<T>* temp;
        temp = head;    //temp is head

        while (temp!=NULL)  //while we dont reach last node
        {


            temp->data->Render(gRenderer);


            temp = temp->next;

        }
    }

    void RenderAll(SDL_Renderer* gRenderer,int frame)
    {
        Node<T>* temp;
        temp = head;    //temp is head

        while (temp!=NULL)  //while we dont reach last node
        {


            temp->data->Render(gRenderer,frame);


            temp = temp->next;

        }
    }
    void CleanAll()
    {
        Node<T>* temp = head;

        while(temp != NULL)
        {

            if(temp == head)
            {

                if(temp->data != NULL)
                {

                    if(temp->data->GetAlive() == false)
                    {

                        head = head->next;

                        if(head!=NULL)
                        {

                            head->prev = NULL;

                        }

                        delete temp;

                        temp = head;


                    }
                    else
                    {
                        temp = temp->next;
                    }
                }
                else
                {
                    break;
                }
            }
            else if(temp == tail)
            {
                if(temp->data!=NULL)
                {
                    if(temp->data->GetAlive() == false)
                    {
                        tail = tail->prev;
                        tail->next = NULL;

                        delete temp;

                        temp = NULL;
                    }
                    else
                    {
                        temp = temp->next;
                    }
                }
            }
            else
            {
                if(temp->data->GetAlive() == false)
                {
                    Node<T>* keeper = temp;
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    temp = temp->next;
                    delete keeper;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
        temp = head;
        while(temp != NULL)
        {
            Node<T>* temp2;
            temp2 = temp;
            while(temp2 != NULL)
            {

                if(temp->data->getPosition()>temp2->data->getPosition())
                {

                    T insideData = temp->data;
                    temp->data = temp2->data;
                    temp2->data = insideData;



                }
                temp2=temp2->next;
            }
            temp=temp->next;
        }
    }


};


