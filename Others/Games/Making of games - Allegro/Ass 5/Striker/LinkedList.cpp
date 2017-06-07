#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
    length = 0;

}

LinkedList::~LinkedList()
{
    Node* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::Append(Object* object)
{
    if (head == NULL)
    {
        head = new Node;
        tail = head;
        head->object = object;
        head->next = NULL;
        head->prev = NULL;
    }
    else
    {
        Node* temp = new Node;
        temp->object = object;
        temp->next = NULL;
        temp->prev = tail;
        tail->next = temp;
        tail = tail->next; //We can also write tail = temp
    }

    length++;
}

Object* LinkedList::Pop()
{
    Object* object = NULL;
    if (length == 0)
    {
        return NULL;
    }

    length--;
    object = tail->object;

    if (tail == head)
    {
        delete tail;
        tail = NULL;
        head = NULL;
        return object;
    }

    tail = tail->prev;
    delete tail->next;
    tail->next = NULL;
    return object;
}

int LinkedList::Length()
{
    return length;
}

void LinkedList::InsertAt(Object* object, int index)
{
    if (head == NULL)
    {
        head = new Node;
        tail = head;
        head->object = object;
        head->next = NULL;
        head->prev = NULL;
    }
    else if(index <= 0)
    {
        Node* temp = new Node;
        temp->object = object;
        temp->next = head;
        temp->prev = NULL;
        head->prev = temp;
        head = temp;
    }
    else if(index >= length)
    {
        Node* temp = new Node;
        temp->object = object;
        temp->next = NULL;
        temp->prev = tail;
        tail->next = temp;
        tail = tail->next; //We can also write tail = temp
    }
    else
    {
        int counter = 0;
        Node* iter = head;

        while(counter < index)
        {
            iter = iter->next;
            counter++;
        }

        Node* temp = new Node;
        temp->object = object;
        temp->next = iter;
        temp->prev = iter->prev;
        iter->prev->next = temp;
        iter->prev = temp;
    }
    length++;
}

Object* LinkedList::DeleteAt(int index)
{
    Object* object = NULL;

    if (head == NULL)
    {
        return NULL;
    }
    if(index >= length)
    {
        Pop();
    }
    if(tail->next == NULL)
    {
        object = tail->object;
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
        length--;
    }
    else
    {
        int counter = 0;
        Node* iter = head;

        while(counter < index)
        {
            iter = iter->next;
            counter++;
        }

        object = iter->object;
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        delete iter;
        length--;
    }
    return object;
}


void LinkedList::CleanAll()
{
    Node* temp = head;
    while(temp != NULL)
    {

        if(temp == head)
        {
            if(temp->object != NULL)
            {
                if(temp->object->Alive() == false)
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
            if(temp->object!=NULL)
            {
                if(temp->object->Alive() == false)
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
            if(temp->object->Alive() == false)
            {
                Node* keeper = temp;
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
}

Node* LinkedList::GetHead()
{
    return head;
}

void LinkedList::MoveAll()
{   //Moves all the objects in the list
    Node* temp = head;
    while(temp!=NULL)
    {
        temp->object->Move();
        temp = temp->next;
    }
}

void LinkedList::CheckCollision(BITMAP* image)
{
    Node* temp = head;  //A new pointer of type Node is created i.e pointing towards head
    while(temp!=NULL)   //This pointer iterates till the end of list
    {
        Node* temp2 = temp->next;   //A second pointer is created that is pointing towards the second element in list
        while(temp2!=NULL)  //This pointer 2 also iterates over a list, this ensures every element is checked with every other element
        {
            bool sametype = temp->object->GetType() == temp2->object->GetType();    //type of both objects are compared
            bool notExplosion = (temp->object->GetType()>-1) && (temp2->object->GetType()>-1);  //It is ensured that object isnt a collision
            if( (!sametype) && (hit(temp->object,temp2->object)) && (notExplosion)) //if objects arent of same type and they arent collision and they hit each other
            {
               Collide(temp->object,temp2->object,image);   //then call function collide and pass both objects to it (they collided exclusively)
            }
            temp2 = temp2->next;
        }
        temp=temp->next;
    }
}

bool LinkedList::hit(Object* object1, Object* object2)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = object1->GetPosition().x;       //left 1 is object 1's x coord
	left2 = object2->GetPosition().x;       //left 2 is object 2's x coord
	right1 = object1->GetPosition().x + object1->GetFrameWidth();   //right 1 is objects 1's x + frame width, that makes it top right coord
	right2 = object2->GetPosition().x + object2->GetFrameWidth();   //right 2 is object 2's top right coord

	top1 = object1->GetPosition().y;    //object 1's y
	top2 = object2->GetPosition().y;    //object 2's y
	bottom1 = object1->GetPosition().y + object1->GetFrameHeight(); //object 1's bottom left
	bottom2 = object2->GetPosition().y + object2->GetFrameHeight(); //object 2's bottom left

	if (bottom1 < top2) return(false);  //if object 1's bottom left is lesser than object 2's top left (not touching)
	if (top1 > bottom2) return(false);  //if object 1's top left is greater than object 2's bottom left (not touching)

	if (right1 < left2) return(false);  //if right line(top right) of object 1 is lesser than left line of object 2
	if (left1 > right2) return(false);  //if left line of object 1 is greater than right line of object 2

	return(true);   //if these conditions are not met, then it is definately colliding

}

void LinkedList::Collide(Object* o1,Object* o2,BITMAP* image)
{
    int healthtemp = o1->GetHealth();
    o1->TakeDamage(o2->GetHealth());    //Takes Damage depending on other objects health
    o2->TakeDamage(healthtemp);

    if(o1->GetHealth()<=0)      //if health falls below 0
    {
        o1->SetAlive(false);    //set the object as dead

        if(o1->GetType()!=1)    //if the object was not bullet
        {
            Explosion* explode = new Explosion(image,46,46,o1->GetPosition().x,o1->GetPosition().y);    //create explosion,
            Append(explode);    //and append it to the list.
        }

    }
    if(o2->GetHealth()<=0)  //same for object 2
    {
        o2->SetAlive(false);


        if(o2->GetType()!=1)
        {
            Explosion* explode = new Explosion(image,46,46,o1->GetPosition().x,o1->GetPosition().y);
            Append(explode);
        }

    }

}

void LinkedList::DrawAll(BITMAP* buffer, bool debug)
{   //Draws all the objects in the list
    Node* temp = head;

    while(temp!=NULL)
    {
        temp->object->Draw(buffer, debug);
        temp = temp->next;
    }


}
