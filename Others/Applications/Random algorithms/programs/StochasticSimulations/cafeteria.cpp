#include <iostream>
#include "cafeteria.h"

#include <iostream>
using namespace std;
// Other includes as necessary.

/**
 * Initialize the queue. Calls the create_queue() function to set the
 * front and rear pointers.
 *
 * Parameters:
 * queue = a pointer of type Queue that represents a queue
 *
 * Return: none
 */

void initializeQueue(Queue *queue) {
   create_queue(queue);
}

/**
 * This is the main schedule of the virtual HU Cafeteria queue.
 * This loop corresponds to the pseudo-code given in the Lab's PDF document.
 *
 * Parameters:
 * queue = a pointer of type Queue that represents a queue
 *
 * Return: none
 */
void schedule(Queue *queue) {
    int currentID = 0;
    int nextArrivalTime = returnNextArrivalTime();
    int c = InitClock;
    int check = nextArrivalTime;
    int serv_cus = 0, serv_time = 0, waiting_time = 0, max_wait = 0;
    Item customer[600];                                //new customer
    setNextArrivalTime(&customer[currentID],nextArrivalTime);
    setServiceTime(&customer[currentID]);           //service time needed for this customer is determined
    for(c=0; c<MaxClock; c++){                      //looping for 600 mins

        if(c==check){         //if the arrival time of the customer is the current time
            enqueue(queue,customer[currentID]);   //put him in queue

            customer[currentID].personID = currentID;
            setServiceBeginTime(&customer[currentID],c);
            setServiceTime(&customer[currentID]);
            currentID ++;
            nextArrivalTime=returnNextArrivalTime();
            setNextArrivalTime(&customer[currentID],nextArrivalTime);   //determine next customers arrival time
            check = check + customer[currentID].arrivalTime;
            customer[currentID - 1].departureTime = customer[currentID-1].serviceBeginTime+customer[currentID-1].serviceTime;
        }
            if((customer[currentID-1].departureTime)==c && currentID > 0){
                serv_cus++;
                serv_time += customer[currentID-1].serviceTime;
                waiting_time += c - customer[currentID-1].arrivalTime;
                if (c - customer[currentID-1].arrivalTime > max_wait)
                    max_wait = c - customer[currentID-1].arrivalTime;
                cout<<"Service for Customer: "<<serv_cus-1<<" is completed"<<endl;
            }
        }
        cout << serv_cus << " customers were served today." << endl;
        cout << serv_time << " minutes were spent serving all the customers." << endl;
        cout << waiting_time << " minutes were spent waiting by the customers." << endl;
        cout << "Average waiting time: " << waiting_time/(serv_cus*1.0) << " minutes" << endl;
        cout << max_wait << " minutes was the maximum waiting time of a customer." << endl;
        if (check > MaxClock)
            cout << "Not all customers were served today." << endl;
        else
            cout << "All customers have been served today." << endl;
    }

/**
 * Set the time at which service begins for this customer. Basically, this
 * would mean that the time at which the queue's front pointer now points to this
 * customer - i.e., this customer is at the front of the queue.
 *
 * Parameters
 * customer = pointer of userdefine type Data to represent a customer
 * time = time at which service begin for the customer
 */
void setServiceBeginTime(Data *customer, int time) {
    customer->serviceBeginTime = time;
}

/**
 * Returns the next arrival time for the next customer in the queue.
 * Notice that in the Lab document, we assume a random number between 1 and 4.
 * The next arrival time of jobs/customers/items in a queue can follow other
 * distributions, such as the Poisson distribution etc.
 * For practice and exploration, try other ways through which the next arrival
 * time may be determined.
 *
 * Parameters: None
 *
 * Return: next arrival time for the next customer
 */
int returnNextArrivalTime() {
    return (rand()%4)+1;//To be implemented.
}

/**
 * Set next arrival time for a customer.
 *
 * Parameters:
 * customer = a pointer of user defined type Data to represents a customer
 * arrivalTime = arrival time of customer
 */
void setNextArrivalTime(Data *customer, int arrivalTime) {
    customer->arrivalTime = arrivalTime;
}

/**
 * Sets the time required to serve a customer in our virtual HU Cafeteria queue.
 * Notice that in the Lab document, we assume a random number between 1 and 4.
 * For practice and exploration, try other ways through which service times
 * may be determined.
 *
 * Parameters:
 * customer = a pointer of user define data type Data to represent a customer
 */
void setServiceTime(Data *customer) {
     customer->serviceTime = (rand()%4)+1; //To be implemented.
}

/**
 * Prints the statistics collected during and at the end of the simulation.
 * Please refer to the Output section in this exercise description.
 *
 * Parameters: None
 * Return: None
 */
void printFinalStatistics() {
     // to be implemented
}

/* starting function of the simulation */

int main(int argc, char** argv) {
    initializeRandomGenerator();

    Queue queue;
    initializeQueue(&queue);
    schedule(&queue);
    printFinalStatistics();
    system("PAUSE");
    return 0;
}
