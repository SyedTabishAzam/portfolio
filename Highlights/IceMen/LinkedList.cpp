#include "LinkedList.h"


template <typename T>
void LinkedList<T>::Push(T data)
{

    if(head == NULL)
    {   //if pointers are null
        Node<T>* temp = new Node<T>;    //create a new node temp
        temp->data = data;  //save data to it
        temp->next = NULL;  //set its next to null
        temp->prev = NULL;  //set its prev to null
        tail = temp;    // set head and tail as this node
        head = temp;
    }
    else
    {   //if head not null, means not first node
        Node<T>* temp = new Node<T>;    //create new node
        temp->data = data;  //set its data
        tail->next = temp;  //set the tail's next to this node
        temp->next = NULL;  //set this node's next to NULL
        temp->prev = tail;  //set this node's prev to the tail
        tail = temp;    //set tail as this node

    }
    length++;
}

template <typename T>
T LinkedList<T>::Pop()
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
        length--;
    }
    else
    {
               //if empty, then return NULL
        return NULL;
    }

}

template <typename T>
void LinkedList<T>::CheckCollision()
{
    Node<T>* temp = head;  //A new pointer of type Node is created i.e pointing towards head
    while(temp!=NULL)   //This pointer iterates till the end of list
    {
        Node<T>* temp2 = temp->next;   //A second pointer is created that is pointing towards the second element in list
        while(temp2!=NULL)  //This pointer 2 also iterates over a list, this ensures every element is checked with every other element
        {
            bool sametype = int(temp->data->GetType()/10) == int(temp2->data->GetType()/10);    //type of both datas are compared
            bool obstacle = int(temp->data->GetType()==30) || int(temp2->data->GetType()==30);


            if( (!sametype) && (hit(temp->data,temp2->data)) && !obstacle) //if datas arent of same type and they arent collision and they hit each other
            {
               Collide(temp->data,temp2->data);   //then call function collide and pass both datas to it (they collided exclusively)
            }
            temp2 = temp2->next;
        }
        temp=temp->next;
    }
}

template <typename T>
void LinkedList<T>::Collide(Object* o1,Object* o2)
{
    if(o1->GetType()==1)
    {
        if(o2->GetType()>=15)
        {
            o2->setAlive(false);
            o1->UsePup(o2->GetType());
        }
        else if(o2->GetState()==NORMAL)
        {
            o1->TakeDamage(o2->GiveDamage());
        }
        else if(o2->GetState()==BALL)
        {
            if((o1->GetX()) > (o2->GetX()))
            {
                    o2->ChangePosition(o2->GetX()-1,o2->GetY());
                    if(key[KEY_SPACE])
                    {
                       o2->ChangeState(BALLMOVE,0);
                    }
            }
            else
            {
                    o2->ChangePosition(o2->GetX()+1,o2->GetY());
                    if(key[KEY_SPACE])
                    {
                        o2->ChangeState(BALLMOVE,0);
                    }
            }

        }

    }
    else if(o2->GetType()==1)
    {
        cout<<o1->GetType()<<" type"<<endl;
        if(o1->GetType()>=15)
        {
            o1->setAlive(false);
            o2->UsePup(o1->GetType());
        }
        else if(o1->GetState()==NORMAL)
        {
            //o2->TakeDamage();
        }
        else if(o1->GetState()==BALL)
        {
            if((o2->GetX()) > (o1->GetX()))
            {
                    o1->ChangePosition(o1->GetX()-1,o1->GetY());
                    if(key[KEY_SPACE])
                    {
                        o1->ChangeState(BALLMOVE,0);
                    }
            }
            else
            {
                    o1->ChangePosition(o1->GetX()+1,o1->GetY());
                    if(key[KEY_SPACE])
                    {
                        o1->ChangeState(BALLMOVE,0);
                    }
            }

        }
    }
    else
    {
        if(o1->GetType()==4 && o2->GetType()<15)
        {
            Push(o2->InstantDeath());
        }
        else if(o2->GetType()==4 && o2->GetType()<15)
        {
            Push(o1->InstantDeath());
        }
        else
        {
            if(o2->GetType()<15)
            {
                o1->TakeDamage(o2->GiveDamage());
            }
            if(o1->GetType()<15)
            {
                o2->TakeDamage(o2->GiveDamage());
            }

        }

    }

}

template <typename T>
bool LinkedList<T>::hit(Object* object1, Object* object2)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = object1->GetX();       //left 1 is object 1's x coord
	left2 = object2->GetX();       //left 2 is object 2's x coord
	right1 = object1->GetX() + object1->GetFrameWidth();   //right 1 is objects 1's x + frame width, that makes it top right coord
	right2 = object2->GetX() + object2->GetFrameWidth();   //right 2 is object 2's top right coord

	top1 = object1->GetY();    //object 1's y
	top2 = object2->GetY();    //object 2's y
	bottom1 = object1->GetY() + object1->GetFrameHeight(); //object 1's bottom left
	bottom2 = object2->GetY() + object2->GetFrameHeight(); //object 2's bottom left

	if (bottom1 < top2) return(false);  //if object 1's bottom left is lesser than object 2's top left (not touching)
	if (top1 > bottom2) return(false);  //if object 1's top left is greater than object 2's bottom left (not touching)

	if (right1 < left2) return(false);  //if right line(top right) of object 1 is lesser than left line of object 2
	if (left1 > right2) return(false);  //if left line of object 1 is greater than right line of object 2

	return(true);   //if these conditions are not met, then it is definately colliding

}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    return (head==NULL);    //if head is NULL, its empty
}

template <typename T>
void LinkedList<T>::Draw(BITMAP* buffer)
{
    Node<T>* temp;
    temp = head;    //temp is head
    while (temp!=NULL)  //while we dont reach last node
    {
        temp->data->Draw(buffer); //output every data
        temp = temp->next;
    }
}

template <typename T>
void LinkedList<T>::Update()
{

    extern vector<Object*> grounds;
    Node<T>* temp;
    temp = head;    //temp is head
    while (temp!=NULL)  //while we dont reach last node
    {
        temp->data->SetGrounds(grounds); //output every data
        temp = temp->next;
    }
    this->Move();
}

template <typename T>
void LinkedList<T>::Move()
{

    Node<T>* temp;
    temp = head;    //temp is head
    while (temp!=NULL)  //while we dont reach last node
    {
        temp->data->Move(); //output every data
        temp = temp->next;
    }
}

template <typename T>
void LinkedList<T>::Save()
{
    ofstream pFile;
    pFile.open("save.txt",ios::trunc);

    Node<T>* temp;
    temp = head;    //temp is head
    while (temp!=NULL)
    {

        temp->data->Save(pFile); //output every data
        temp = temp->next;

    }
    pFile<<"$";
    pFile.close();
}


template <typename T>
int LinkedList<T>::GetLength()
{
    return length;
}

template <typename T>
void LinkedList<T>::CleanAll()
{
    Node<T>* temp = head;

    while(temp != NULL)
    {

        if(temp == head)
        {

            if(temp->data != NULL)
            {

                if(temp->data->isAlive() == false)
                {
                    cout<<"deleted1"<<endl;

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
                if(temp->data->isAlive() == false)
                {
                    cout<<"deleted3"<<endl;
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

            if(temp->data->isAlive() == false)
            {
                cout<<"deleted4"<<endl;
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
}
