#include "queue.h"
#include <stdlib.h>

Queue createQueue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return *queue;
}

void enQueue(Queue *queue,void *data) {
	QueueNodePtr QNode = malloc(sizeof(QueueNode));
	QNode->data = data;
	if(queue->head == NULL)queue->head = QNode;
	else queue->tail->next = QNode;
	queue->tail = QNode;
}

void *deQueue(Queue *queue) {
	void *deletableItem = queue->head->data;
	queue->head = queue->head->next;
	return deletableItem;
}