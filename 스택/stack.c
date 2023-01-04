#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
	char value;
	struct LinkedNode* next;
} linkedNode;

typedef struct Stack {
	linkedNode* top;
	int size;
} stack;

linkedNode newNode(char value) {
	linkedNode myNode;
	myNode.value = value;
	myNode.next = NULL;

	return myNode;
}

stack create() {
	stack myStack;
	myStack.top = NULL;
	myStack.size = 0;

	return myStack;
}

void push(stack* myStack, char value) {
	linkedNode topNode = newNode(value);
	if (myStack->size) {
		topNode.next = myStack->top;
	}
	myStack->top = malloc(sizeof(linkedNode));
	*(myStack->top) = topNode;
	myStack->size++;
}

char pop(stack* myStack) {
	if (myStack->size == 0) {
		return NULL; // underflow
	}

	char value = myStack->top->value;
	linkedNode* currentTop = myStack->top;
	if (myStack->size == 1) {
		myStack->top = NULL;
	}
	else {
		myStack->top = myStack->top->next;
	}

	free(currentTop);
	myStack->size--;
	return value;
}

void print(stack* myStack) {
	stack tempStack = create();
	
	int size = myStack->size;
	for (int i = 0; i < size; i++) {
		char value = pop(myStack);
		printf("%c ", value);
		push(&tempStack, value);
	}
	for (int i = 0; i < size; i++) {
		push(myStack, pop(&tempStack));
	}
	printf("\n");
}

int isMember(stack* myStack, char value) {
	stack tempStack = create();
	int size = myStack->size;
	int isIn = 0;
	for (int i = 0; i < size; i++) {
		char tempValue = pop(myStack);
		push(&tempStack, tempValue);
		if (value == tempValue) {
			isIn = 1;
			break;
		}
	}
	size = tempStack.size;
	for (int i = 0; i < size; i++) {
		push(myStack, pop(&tempStack));
	}

	return isIn;
}

int main() {
	stack myStack = create();
	push(&myStack, 'a');
	printf("%c\n", pop(&myStack));

	push(&myStack, 'b');
	push(&myStack, 'c');
	push(&myStack, 'd');

	print(&myStack);
	print(&myStack);

	printf("is 'a' in stack? %d\n", isMember(&myStack, 'a'));
	printf("is 'c' in stack? %d\n", isMember(&myStack, 'c'));
}