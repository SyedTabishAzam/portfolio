#include "queue.h"
#include <cstddef>
#include <iostream>

/** Creates a new queue. Queue pointers are initialized.
    Parameter:
    queue = a pointer of type Queue that represents a queue

    Return: none
*/
void create_queue(Queue *queue) {
   queue->frontptr = NULL;
   queue->rearptr = NULL;
}

/** Checks if the queue is Empty.

    Parameters:
    queue = a pointer of type Queue that represents a queue

    Return:
    True when queue is empty otherwise false.
*/
Boolean isEmptyQueue(Queue *queue) {
    return queue->frontptr == NULL ? TRUE : FALSE;
}

 /**
 *  Destroys the contents of a queue. We iterate over all items in the
  * queue until the queues becomes empty (use isEmptyQueue(...).
  * We can just set both queue->frontptr and queue->rearptr are reset to NULL
  * but we want to dispose off (do garbage collection) all the nodes in the queue
  * - i.e., do the chores.
  *
  * Here's the pseudo-code
  * while (queue is not empty) {
  *    i. temp = queue->front; // we want to remove the front node in the queue
  *    ii. now move on to the next node and update the front pointer of the queue.
  *    iii. Dispose of the temp pointer using free (for C) or delete (C++).
  * }
  * Parameters
  * queue = a pointer of type Queue that represents a queue
  *
  * Return: none
 */
void kill_queue(Queue *queue) {
    Queue_Node *temp;
    while (isEmptyQueue(queue) == FALSE) {
        temp = queue->frontptr;
        queue->frontptr = queue->frontptr->nextptr;
        delete temp;
    }
    //at this stage both queue->frontptr and queue->rearptr are reset to NULL.
    queue->rearptr = NULL;
}

/**
 *  Enqueue a new data item of type Data at the rear of the queue.
 * You will have to create a new node of type Queue_Node using dynamic allocation.
 * For that you can use malloc(...) in C or new in C++ [preferred].
 * Once a pointer to a new object of type Queue_Node is returned, call it newNode
 *     we need to pass the data by newNode->data = data; newNode->next = NULL;
 *     and then we need to check, whether the queue is empty. If it is then
 *          both the frontptr and rearptr need to be updated.
 *          If the queue is not empty then only the rearptr needs updating.
 *
 * Parameters:
 * queue = a pointer of type Queue that represents a queue
 * data = a variable of userdefined data type Data represents a customer
 */
void enqueue(Queue *queue, Data data) {
     // you can use new in C++ [recommended]
    Queue_Node *newNode = new Queue_Node[sizeof(Queue_Node)];
    newNode->data = data;
    newNode->nextptr = NULL;
    if (isEmptyQueue(queue) == 1)
        queue->frontptr = newNode;
    else
        queue->rearptr->nextptr = newNode;
    queue->rearptr = newNode;
}

/**
 * Dequeue front item from the queue.
 *
 * First make sure that the queue is not empty, otherwise nothing happens.
 *
 * We need to ensure that the dequeued item is not lost. So we first store its
 * pointer in a temporary pointer of type Queue, say temp.
 * Then retrieve data from the first item in the queue and pass it on to ptr.
 * Point the frontptr to the next item in the queue.
 * We can now remove the front node from the queue and then call free(...) or
 * delete(...) to dispose off the temp pointer.

 * One thing to check is that if the removed node was the only node in the queue,
 * then in this case, the rearptr needs updating as well.
 *
 * Parameters:
 * queue = a pointer of type Queue that represents a queue
 * dataptr = a pointer of type Data that represents a customer
 */
void dequeue(Queue *queue, Data &dataptr) {
    Queue_Node *temp;
    /*
     * If (there is a node in the queue to be removed)
     *  Then
     *      dataptr = queue->front-> data ...
     *      temp = queue->front
     * ... and so on.
     *     */
    if (isEmptyQueue(queue) == FALSE) {
        dataptr=queue->frontptr->data;
        temp=queue->frontptr;
        queue->frontptr = queue->frontptr->nextptr;
        delete temp;
    }
}
