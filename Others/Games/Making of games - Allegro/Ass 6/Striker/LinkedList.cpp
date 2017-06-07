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

int LinkedList::Length()
{
    return length;
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
        if((rand()%100)==0)
        {   //create randomly the fire of enemy objects
            if(temp->object->Fire()!=NULL && temp->object->GetType()>12)
                Append(temp->object->Fire());   //and append it to list
        }
        temp = temp->next;

    }
}

void LinkedList::CheckCollision(BITMAP* image,Player* fighter)
{
    Node* temp = head;  //A new pointer of type Node is created i.e pointing towards head
    while(temp!=NULL)   //This pointer iterates till the end of list
    {
        Node* temp2 = temp->next;   //A second pointer is created that is pointing towards the second element in list
        while(temp2!=NULL)  //This pointer 2 also iterates over a list, this ensures every element is checked with every other element
        {
            bool sametype = int(temp->object->GetType()/10) == int(temp2->object->GetType()/10);    //type of both objects are compared
            bool notExplosion = (temp->object->GetType()!=-1) && (temp2->object->GetType()!=-1);  //It is ensured that object isnt a collision
            bool planepowerup = ((temp->object->GetType() ==1) && (temp2->object->GetType()>20)) || ((temp->object->GetType() >20) && (temp2->object->GetType()==1));

            if( (!sametype) && (hit(temp->object,temp2->object)) && (notExplosion)) //if objects arent of same type and they arent collision and they hit each other
            {

                if(planepowerup)    //if plane receives powerup
                {

                    int armourtype;
                    (temp->object->GetType()==1) ? (armourtype= temp2->object->GetType()) : (armourtype=temp->object->GetType()); //get powerup type and store in armourtype
                    (temp->object->GetType()==1) ? (temp2->object->SetAlive(false)) : (temp->object->SetAlive(false));  //set setalive of powerup to false

                    fighter->UsePuP(armourtype % 20);   //pass the armour type mod 20 ( so basically 1,2,or 3 is passed) to fighter's method


                }
                else if(temp->object->GetType()<21 && temp2->object->GetType()<21)
                {
                    //if it is not powerup, make collision
                    Collide(temp->object,temp2->object,image);   //then call function collide and pass both objects to it (they collided exclusively)

                }
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
        if(o1->GetType()>12)    //if the object was not bullet
        {
            Explosion* explode = new Explosion(image,46,46,o1->GetType(),o1->GetPosition().x,o1->GetPosition().y);    //create explosion,
            Append(explode);    //and append it to the list.
            int randompup = rand()%100;
            if(randompup>50)    //there are 50 % chances of powerup generation
            {   //generate powerups on death of enemy
                Powerups* power = new Powerups(image,randompup,o1->GetPosition());
                Append(power);  //append powerup to the list
            }
        }
    }
    if(o2->GetHealth()<=0)  //same for object 2
    {
        if(o2->GetType()>12)
        {
            Explosion* explode = new Explosion(image,46,46,o2->GetType(),o2->GetPosition().x,o2->GetPosition().y);
            Append(explode);
            int randompup = rand()%100;
            if(randompup>50)
            {
                Powerups* power = new Powerups(image,randompup,o2->GetPosition());
                Append(power);
            }
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

