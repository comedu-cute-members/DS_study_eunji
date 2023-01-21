#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
	char value;
	struct LinkedNode* next;
} linkedNode;

typedef struct Queue {
	linkedNode* front;
	linkedNode* rear;
} queue;

queue create() {
	queue myQueue;
	myQueue.front = NULL;
	myQueue.rear = NULL;

	return myQueue;
}

linkedNode newNode(char value) {
	linkedNode myNode;
	myNode.value = value;
	myNode.next = NULL;

	return myNode;
};

void enqueue(queue* myQueue, char value) {
	linkedNode tempNode = newNode(value);

	if (myQueue->front == NULL) {  // first enqueue
		myQueue->front = malloc(sizeof(linkedNode));
		*(myQueue->front) = tempNode;
		myQueue->rear = myQueue->front;
	}
	else {
		myQueue->rear->next = malloc(sizeof(linkedNode));
		*(myQueue->rear->next) = tempNode;
		myQueue->rear = myQueue->rear->next;
	}
}

char dequeue(queue* myQueue) {
	if (myQueue->front == NULL) {
		return NULL;
	}
	
	char value = myQueue->front->value;

	if (myQueue->front == myQueue->rear) {  // item count: 1
		myQueue->front = NULL;
		myQueue->rear = NULL;
	}
	else myQueue->front = myQueue->front->next;
	
	return value;
}

int isEmpty(queue* myQueue) {
	if (myQueue->front == NULL) return 1;
	else return 0;
}

char peek(queue* myQueue) {
	return myQueue->front->value;
}

void printQueue(queue* myQueue) {
	if (myQueue->front) {
		linkedNode* current = myQueue->front;
		int index = 0;

		while (current) {
			printf("%d: %c\n", index, current->value);
			current = current->next;
			index++;
		}
	}
}

int countQueue(queue* myQueue) {
	int count = 0;
	if (myQueue->front) {
		linkedNode* current = myQueue->front;

		while (current) {
			count++;
			current = current->next;
		}
	}

	return count;
}

int main() {
	queue myQueue = create();
	// printf("queue: %p\n", &myQueue);

	enqueue(&myQueue, 'a');
	enqueue(&myQueue, 'b');

	printf("%c\n", dequeue(&myQueue));
	printf("%c\n", dequeue(&myQueue));

	printf("%s\n", (isEmpty(&myQueue)) ? "empty" : "not empty");

	enqueue(&myQueue, 'c');
	printf("%s\n", (isEmpty(&myQueue)) ? "empty" : "not empty");

	printf("%c\n", peek(&myQueue));
	printf("%s\n", (isEmpty(&myQueue)) ? "empty" : "not empty");

	enqueue(&myQueue, 'd');
	enqueue(&myQueue, 'e');
	printQueue(&myQueue);

	printf("queue length: %d\n", countQueue(&myQueue));
}