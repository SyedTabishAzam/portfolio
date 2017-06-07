#pragma once
#include <iostream>

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
public:
    DoubleLinkedList()
    {   //initialize and keep pointers NULL
        head = NULL;
        tail = NULL;
    }

    ~DoubleLinkedList()
    {
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
            cout<<"Pushing: "<<tail->data<<endl;    //output whatever is being pushed
        }
        else
        {   //if head not null, means not first node
            Node<T>* temp = new Node<T>;    //create new node
            temp->data = data;  //set its data
            tail->next = temp;  //set the tail's next to this node
            temp->next = NULL;  //set this node's next to NULL
            temp->prev = tail;  //set this node's prev to the tail
            tail = temp;    //set tail as this node
            cout<<"Pushing: "<<tail->data<<endl;    //output whatever is pushed
        }

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
                return x;   //return the stored data
            }
            else
            {   //if not the last node
                Node<T>* temp = new Node<T>;    //create new temp node
                temp = tail;    //set temp to tail
                tail = tail->prev;  //set tail as the previous of tail
                tail->next = NULL;  //set the next of the current tail as NULL
                T x = temp->data;   //save the data in the TO-BE-REMOVED node
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
};


