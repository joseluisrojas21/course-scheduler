#include <stdlib.h>
#include <stdio.h>

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue *makeQueue() {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue) {
    return (queue->front == NULL);
}

void enqueue(Queue *queue, void *data) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Could not allocate memory for a new node\n");
        exit(-1);
    }
    
    newNode->data = data;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void *dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    QueueNode *frontNode = queue->front;
    void *frontData = frontNode->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(frontNode);
    return frontData;
}

void freeQueue(Queue *queue) {
    QueueNode *curr = queue->front;
    while (curr != NULL) {
        QueueNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(queue);
}