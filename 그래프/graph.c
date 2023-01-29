#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
    char vertex;
    struct LinkedNode* next;
} linkedNode;

typedef struct LinkedList {
    char vertex;
    linkedNode* front;
} linkedList;

typedef struct Graph {
    int maxSize;
    int size;
    linkedList* adjacencyList;
} graph;

graph init(int maxSize) {
    graph myGraph;
    myGraph.maxSize = maxSize;
    myGraph.size = 0;
    myGraph.adjacencyList = malloc(maxSize * sizeof(linkedList));

    return myGraph;
}

void insertVertex(graph* myGraph, char vertex) {
    if (myGraph->size == myGraph->maxSize) {
        printf("This graph is full.\n");
    }
    else {
        linkedList newList;
        newList.front = malloc(sizeof(linkedNode));
        newList.front->next = NULL;
        newList.front->vertex = vertex;
        newList.vertex = vertex;
        myGraph->adjacencyList[myGraph->size] = newList;
        myGraph->size++;
    }
}

int isInGraph(graph* myGraph, char vertex) {
    for (int i = 0; i < myGraph->size; i++) {
        if (myGraph->adjacencyList[i].vertex == vertex) return 1;
    }
    return 0;
}

void addNode(linkedList* myList, char vertex) {
    linkedNode newNode;
    newNode.vertex = vertex;
    newNode.next = NULL;

    linkedNode* current = myList->front;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(linkedNode));
    *(current->next) = newNode;
}

void insertEdge(graph* myGraph, char vertex1, char vertex2) {
    if (isInGraph(myGraph, vertex1) && isInGraph(myGraph, vertex2)) {
        for (int i = 0; i < myGraph->size; i++) {
            if (myGraph->adjacencyList[i].vertex == vertex1) {
                addNode(&myGraph->adjacencyList[i], vertex2);
                break;
            }
        }

        for (int i = 0; i < myGraph->size; i++) {
            if (myGraph->adjacencyList[i].vertex == vertex2) {
                addNode(&myGraph->adjacencyList[i], vertex1);
                break;
            }
        }
    }
}

void isEmpty(graph* myGraph) {
    if (myGraph->size == 0) printf("This graph is empty.\n");
    else if (myGraph->size == myGraph->maxSize) printf("This graph is full.\n");
    else printf("This graph is not empty.\n");
}

void deleteEdge(graph* myGraph, char vertex1, char vertex2) {
    int i;
    for (i = 0; i < myGraph->size; i++) {
        if (myGraph->adjacencyList[i].vertex == vertex1) break;
    }
    
    linkedNode* current = myGraph->adjacencyList[i].front;
    while (1) {
        if (current->next == NULL) break;
        else if (current->next->vertex == vertex2) break;
        else current = current->next;
    }

    if (current->next != NULL && current->next->vertex == vertex2) {
        current->next = current->next->next;
    }

    for (i = 0; i < myGraph->size; i++) {
        if (myGraph->adjacencyList[i].vertex == vertex2) break;
    }

    current = myGraph->adjacencyList[i].front;
    while (1) {
        if (current->next == NULL) break;
        else if (current->next->vertex == vertex1) break;
        else current = current->next;
    }

    if (current->next != NULL && current->next->vertex == vertex1) {
        current->next = current->next->next;
    }
}

void deleteVertex(graph* myGraph, char vertex) {
    for (int j = 0; j < myGraph->size; j++) {
        if (myGraph->adjacencyList[j].vertex != vertex) deleteEdge(myGraph, myGraph->adjacencyList[j].vertex, vertex);
    }

    int i;
    for (i=0; i < myGraph->size; i++) {
        if (myGraph->adjacencyList[i].vertex == vertex) break;
    }

    for (; i < myGraph->size-1; i++) {
        myGraph->adjacencyList[i] = myGraph->adjacencyList[i + 1];
    }
    myGraph->adjacencyList[i].front = NULL;
    myGraph->adjacencyList[i].vertex = NULL;

    myGraph->size--;
}

void printGraph(graph* myGraph) {
    for (int i = 0; i < myGraph->size; i++) {
        linkedList edge = myGraph->adjacencyList[i];
        printf("%c: ", edge.vertex);
        linkedNode* currentEdge = edge.front->next;
        while (1) {
            if (currentEdge != NULL) {
                printf("->%c", currentEdge->vertex);
                currentEdge = currentEdge->next;
            }
            else break;
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    graph myGraph = init(5);
    
    insertVertex(&myGraph, 'A');

    printf("%s\n\n", isInGraph(&myGraph, 'A') ? "A is in graph" : "A is not in graph");

    insertVertex(&myGraph, 'B');
    insertVertex(&myGraph, 'C');
    insertVertex(&myGraph, 'D');
    insertVertex(&myGraph, 'E');

    insertEdge(&myGraph, 'A', 'B');
    insertEdge(&myGraph, 'A', 'C');
    insertEdge(&myGraph, 'D', 'E');

    printGraph(&myGraph);
    
    deleteEdge(&myGraph, 'A', 'B');
    printGraph(&myGraph);

    deleteVertex(&myGraph, 'A');
    printGraph(&myGraph);

    return 0;
}