typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;
typedef struct queue Queue;

struct queueNode {
	void *data;
	QueueNodePtr next;
};

struct queue{
	QueueNodePtr head;
	QueueNodePtr tail;
};

Queue createQueue();
void enQueue(Queue *queue,void *data);
void *deQueue(Queue *queue);
