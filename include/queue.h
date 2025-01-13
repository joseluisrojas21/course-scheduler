#ifndef queue_H
#define queue_H

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue *makeQueue();
int isEmpty(Queue *queue);
void enqueue(Queue *queue, void *data);
void* dequeue(Queue *queue);
void freeQueue(Queue *queue);

#endif