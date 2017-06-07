#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct NodeS
{   //for Circular but Single, we need node only with next pointer and data storer
    T data;
    NodeS* next;
};

template <typename T>
class SingleCircularList
{
private:
    NodeS<T>* head;  //Whenever you use a template, you need to specify for which data type
    NodeS<T>* tail;
public:
    SingleCircularList()
    {
        head = NULL;
        tail = NULL;
    }

    ~SingleCircularList()
    {
        delete head;
        delete tail;
        cout<<"Single Circular List Destroyed"<<endl;
    }

    void Push(T data)
    {
        if(head == NULL)
        {   //if head is NULL, means list empty
            NodeS<T>* temp = new NodeS<T>;  //create new node
            temp->data = data;  //set data
            temp->next = temp;  //the next is pointing towards itself

            tail = temp;    //tail and head are set to be this new node
            head = temp;
            cout<<"Pushing: "<<tail->data<<endl;
        }
        else
        {
            NodeS<T>* temp = new NodeS<T>;  //if the list wasnt empty, create a new node
            temp->data = data;  //set data
            tail->next = temp;  //the tail (prev node) is now pointing towards this new node
            temp->next = head;  //the next of this node is now pointing towards head
            tail = temp;        //tail is now this current new node
            cout<<"Pushing: "<<tail->data<<endl;
        }

    }

    T Pop()
    {   //since we only have next reference, we traverse from head

        if(!isEmpty())
        {   //if list not empty, then only can pop
            if(head == tail)
            {   //if head = tail (only one node remaining
                T x = tail->data;   //save the data in x
                delete tail;    //delete tail
                tail = NULL;    //set tail as NULL
                head = NULL;    //set head as NULL
                return x;       //return x
            }
            else
            {
                NodeS<T>* temp = new NodeS<T>;  //if not the last node remaning, create new node
                temp = head;    //set  this node as head
                head = head->next;  //head is now pointing towards  its next
                tail->next = head;  //tail's next is now pointing towards new head
                T x = temp->data;   //save the head data
                delete temp;    //delete the old head
                return x;
            }
        }
        else
        {
            T x;    //if list was empty, return garbage
            return x;
        }

    }

    bool isEmpty()
    {
        return (head==NULL);
    }

    void Display()
    {
        NodeS<T>* temp;     //create new node temp such that
        temp = head;    //temp = head
        cout<<temp->data<<endl; //output temp data once and
        temp = temp->next;  //make temp's next as temp (temp is now not same as head)
        while (temp!=head)  //while head and temp doesnt become same again
        {
            cout<<temp->data<<endl; //keep printing all the data
            temp = temp->next;
        }
    }


};


