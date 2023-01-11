#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
	int value;
	struct LinkedNode* next;
	struct LinkedNode* prev;
} linkedNode;

linkedNode NewNode(int value) {
	linkedNode newNode;
	newNode.value = value;
	newNode.next = NULL;
	newNode.prev = NULL;

	return newNode;
}

typedef struct LinkedList {
	linkedNode* head;
	linkedNode* tail;
} linkedList;

linkedList create() {
	linkedList myList;
	myList.head = malloc(sizeof(linkedNode));
	myList.tail = NULL;

	return myList;
}

void addTail(linkedList* myList, int value) {

	if (myList->tail == NULL) { // first node
		*(myList->head) = NewNode(value);
		myList->tail = myList->head;
	}
	else {
		myList->tail->next = malloc(sizeof(linkedNode));
		*(myList->tail->next) = NewNode(value);
		myList->tail->next->prev = myList->tail;
		myList->tail = myList->tail->next;
	}
}

int getItem(linkedList* myList, int index) {
	linkedNode* current = myList->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->value;
}

void printList(linkedList* myList) {
	linkedNode* current = myList->head;

	while (1) {
		printf("%d\n", current->value);

		if (current == myList->tail) break;

		current = current->next;
	}
}

int listCount(linkedList* myList) {
	linkedNode* current = myList->head;
	int count = 0;

	while (1) {
		count++;

		if (current == myList->tail) break;

		current = current->next;
	}

	return count;
}

void delete(linkedList* myList, int index) {

	// current 이동
	linkedNode* current = myList->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	// 요소 삭제
	if (index + 1 == listCount(myList)) { // tail을 삭제한 경우
		myList->tail = current->prev;
	}
	else if (index == 0) {
		myList->head = current->next;
	}
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
}

int main() {
	linkedList myList = create();
	// printf("head: %d  tail: %d\n", myList.head, myList.tail);

	addTail(&myList, 3);
	// printf("head: %d  tail: %d\n", myList.head, myList.tail);

	addTail(&myList, 16);
	// printf("head: %d  tail: %d\n", myList.head, myList.tail);

	addTail(&myList, 25);
	// printf("head: %d  tail: %d\n", myList.head, myList.tail);

	addTail(&myList, 100);

	printList(&myList);
	printf("3번째를 구하는 getItem() 결과: %d\n", getItem(&myList, 2)); // 3번째 값

	delete(&myList, 3);
	printList(&myList);

	printf("연결 리스트의 길이는 %d\n", listCount(&myList));
}