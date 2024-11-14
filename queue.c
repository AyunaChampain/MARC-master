//
// Created by flasque on 19/10/2024.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */

#define MAX 3

t_queue createQueue(int size)
{
    // the size of the queue must be positive
    assert(size > 0);
    t_queue queue;
    queue.size = size;
    queue.first = 0;
    queue.last = 0;
    queue.values = (t_position *)malloc(size * sizeof(t_position));
    return queue;
}
int isQueueEmpty(t_queue q)
{
    return (q.first == q.last);
}

int isQueueFull(t_queue q)
{
    return (q.last-q.first == MAX);
}
void enqueue(t_queue *p_queue, t_position pos)
{
    // the queue must not be full
    assert((p_queue->last - p_queue->first) < p_queue->size);
    p_queue->values[(p_queue->last) % p_queue->size] = pos;
    p_queue->last++;
    return;
}

t_position dequeue(t_queue *p_queue)
{
    // the queue must not be empty
    assert(p_queue->last != p_queue->first);
    p_queue->first++;
    return p_queue->values[(p_queue->first - 1) % p_queue->size];
}
void displayQueue(t_queue q)
{
    printf(" out <- ");
    for (int cpt = q.first ; cpt < q.last; cpt++)
    {
        printf("%d <- ", q.values[cpt%MAX].x);
    }

    printf("in\n");

    return;
}