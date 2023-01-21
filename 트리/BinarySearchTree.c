#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
	int value;
	char leftOrRight;
	struct LinkedNode* left;
	struct LinkedNode* right;
	struct LinkedNode* parent;
} linkedNode;

typedef struct BinarySearchTree {
	linkedNode* root;
} bst;

bst create() {
	bst myBst;
	myBst.root = NULL;

	return myBst;
}

void insertNode(bst* myBst, int value) {
	linkedNode newNode;
	newNode.value = value;
	newNode.left = newNode.right = NULL;
	newNode.leftOrRight = 'n';

	linkedNode* current = NULL;
	linkedNode* nextStep = myBst->root;
	while (nextStep != NULL) {
		current = nextStep;
		if (current->value > value) {
			nextStep = current->left;
			newNode.leftOrRight = 'l';
		}
		else {
			nextStep = current->right;
			newNode.leftOrRight = 'r';
		}
	}

	newNode.parent = current;

	if (newNode.leftOrRight == 'l') {
		current->left = malloc(sizeof(linkedNode));
		*(current->left) = newNode;
	}
	else if (newNode.leftOrRight == 'r') {
		current->right = malloc(sizeof(linkedNode));
		*(current->right) = newNode;
	}
	else {
		myBst->root = malloc(sizeof(linkedNode));
		*(myBst->root) = newNode;
	}
	
}

int isEmpty(bst* myBst) {
	if (myBst->root == NULL) return 1;
	else return 0;
}

void descent(bst* myBst, linkedNode* targetNode) {
	if (targetNode->left == NULL && targetNode->right == NULL) {  // leaf
		if (targetNode->leftOrRight == 'l') targetNode->parent->left = NULL;
		else if (targetNode->leftOrRight == 'r') targetNode->parent->right = NULL;
		else myBst->root = NULL;
	}
	else {
		char descentWho;
		getchar();
		printf("어느쪽을 후계자로 하겠습니까? (l/r): ");
		scanf("%c", &descentWho);

		linkedNode* current;
		if (descentWho == 'l') {
			current = targetNode->left;
			while (current->right) current = current->right;
		}
		else {
			current = targetNode->right;
			while (current->left) current = current->left;
		}

		if (targetNode->parent != NULL) {
			if (targetNode->leftOrRight == 'l') {
				targetNode->parent->left = current;
			}
			else if (targetNode->leftOrRight == 'r') {
				targetNode->parent->right = current;
			}

			if (descentWho == 'l') {
				current->right = targetNode->right;
			}
			else if (descentWho == 'r') {
				current->left = targetNode->left;
			}

			current->parent = targetNode->parent;
		}
		else {  // root
			myBst->root = current;
			if (descentWho == 'l') {
				current->right = targetNode->right;
			}
			else if (descentWho == 'r') {
				current->left = targetNode->left;
			}
			current->leftOrRight = 'n';
		}
	}

	free(targetNode);
}

void traverse(bst* myBst, linkedNode* currentNode, int target) {
	if (currentNode != NULL) {
		if (target > 0 && target == currentNode->value) {
			descent(myBst, currentNode);
		}
		else {
			if (target == -1) printf("%d ", currentNode->value);
			traverse(myBst, currentNode->left, target);
			traverse(myBst, currentNode->right, target);
		}
	}
}

void printBst(linkedNode* currentNode) {
	if (currentNode != NULL) {
		printf("%d", currentNode->value);
		if (currentNode->left || currentNode->right) {
			printf("(");
			printBst(currentNode->left);
			printf(",");
			printBst(currentNode->right);
			printf(")");
		}
	}
}

void traversal(bst* myBst) {
	if (isEmpty(myBst)) printf("Tree is Empty.\n");
	else {
		traverse(myBst, myBst->root, -1);
		printf("\n");
	}
}

int getMin(bst* myBst) {
	if (isEmpty(myBst)) return -1;
	else {
		linkedNode* current = myBst->root;
		while (current->left != NULL) current = current->left;

		return current->value;
	}
}

int getMax(bst* myBst) {
	if (isEmpty(myBst)) return -1;
	else {
		linkedNode* current = myBst->root;
		while (current->right != NULL) current = current->right;

		return current->value;
	}
}

void delete(bst* myBst, int target) {
	traverse(myBst, myBst->root, target);
}

int main() {

	bst myBst = create();
	insertNode(&myBst, 8);
	insertNode(&myBst, 3);
	insertNode(&myBst, 10);
	insertNode(&myBst, 9);
	insertNode(&myBst, 2);
	insertNode(&myBst, 5);
	insertNode(&myBst, 4);
	insertNode(&myBst, 14);
	insertNode(&myBst, 11);
	insertNode(&myBst, 16);

	printf("%s\n", isEmpty(&myBst) ? "empty" : "not empty");
	
	traversal(&myBst);

	printf("min: %d\n", getMin(&myBst));
	printf("max: %d\n", getMax(&myBst));

	printBst(myBst.root);
	printf("\n");

	int deleteValue;
	printf("삭제할 값: ");
	scanf("%d", &deleteValue);
	delete(&myBst, deleteValue, 'n');

	printBst(myBst.root);

	return 0;
}