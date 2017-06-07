/* "Include guard" - prevents this file from getting included more
   than once. */
#ifndef CAFETERIA_H
#define	CAFETERIA_H
#include "queue.h"
#include "queue.cpp"
#include <time.h>
#include <cstdlib>

/* See cafeteria.cpp files for implementation details */

// Value of clock at starting of simulation
const int InitClock = 1;
// Maximum value of clock for simulation
const int MaxClock = 100;

/* Initialize the queue. */
void initializeQueue(Queue *);

/* Returns the next arrival time for the next customer in the queue. */
int returnNextArrivalTime();

/* This is the main schedule of the virtual HU Cafeteria queue. */
void schedule(Queue *);

/* Set next arrival time for a customer */
void setNextArrivalTime(Data *, int);

/* Sets the time required to serve a customer in our virtual HU Cafeteria queue.*/
void setServiceTime(Data *);

/* Set the time at which service begins for this customer. */
void setServiceBeginTime(Data *, int);

/* Prints the statistics collected during and at the end of the simulation. */
void printFinalStatistics();

/* Initialize random number generator*/
inline void initializeRandomGenerator() {
       time_t t;
       srand((unsigned) time(&t));
}
#endif	/* CAFETERIA_H */

