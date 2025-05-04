#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertAtEnd(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);
void swap(Node* a, Node* b);

#endif
