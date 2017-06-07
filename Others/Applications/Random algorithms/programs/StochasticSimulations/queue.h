/* "Include guard" - prevents this file from getting included more
   than once. */   
#ifndef QUEUE_H
#define	QUEUE_H

#include "data.h" // contains data type for customer

/* For Resources on Enumeration
   http://en.cppreference.com/w/cpp/language/enum
   http://www.cplusplus.com/doc/tutorial/other_data_types/
*/ 
enum Boolean {FALSE=0, TRUE=1};

/* For resources on struct
   http://www.cplusplus.com/doc/tutorial/structures/
*/

// Represents a node of linked list
typedef struct node {
    Data data; //User-defined data type (see data.h)
    node *nextptr;     
} Queue_Node; 


/*
 A structure that represents a queue. One can create multile 
 queues by just creating multiple instances of this structure
*/
typedef struct QueueStruct {
    Queue_Node *frontptr; //pointer to the front of the queue
    Queue_Node *rearptr; //pointer to the rear of the queue
} Queue;


/* You have to provide implementation of following functinos in queue.cpp file. 
   The description of each function is described in .cpp file.
*/

/** Creates a new queue. Queue pointers are initialized. */
void create_queue(Queue *);

/** Destroys the passed queue. Memory is freed.*/
void kill_queue(Queue *);

/** Enqueue a new data item of type Data at the rear of the queue. */
void enqueue (Queue *, Data);

/** Dequeue front item from the queue. */
void dequeue (Queue *, Data);

/** Checks if the queue is Empty. */
Boolean isEmptyQueue(Queue *);

#endif	/* QUEUE_H */


