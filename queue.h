//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_QUEUE_H
#define UNTITLED1_QUEUE_H
#include "loc.h"


typedef struct s_queue
{
    t_position *values;
    int size;
    int last;
    int first;
} t_queue;

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createQueue(int);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueue(t_queue *,t_position);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
t_position dequeue(t_queue *);

/**
 * @brief Structure for the queue of integers
 */
typedef struct s_queue_int
{
    int *values;
    int size;
    int last;
    int first;
} t_queue_int;

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue_int createQueueint(int);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueueint(t_queue_int *,int);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
int dequeueint(t_queue_int *);



#endif //UNTITLED1_QUEUE_H