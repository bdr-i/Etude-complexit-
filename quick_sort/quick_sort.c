#include <stdlib.h>
#include <stdio.h>
#include "quick_sort.h"

int partition(Node* start, Node* end, Node** newPivot) {
    if (!start || start == end) return 0;

    int pivotVal = end->data;
    Node* i = start;
    Node* j = start;

    while (j != end) {
        if (j->data < pivotVal) {
            swap(i, j);
            i = i->next;
        }
        j = j->next;
    }

    swap(i, end);
    *newPivot = i;
    return 1;
}

void quickSortUtil(Node* start, Node* end) {
    if (!start || start == end || start == end->next) return;

    Node* pivot = NULL;

    if (partition(start, end, &pivot)) {
        Node* temp = start;
        Node* prev = NULL;

        while (temp != pivot) {
            prev = temp;
            temp = temp->next;
        }

        if (prev) quickSortUtil(start, prev);
        if (pivot && pivot->next) quickSortUtil(pivot->next, end);
    }
}

void quickSortRecursive(Node** headRef) {
    if (!headRef || !*headRef || !(*headRef)->next) return;

    Node* end = *headRef;
    while (end->next) {
        end = end->next;
    }
    quickSortUtil(*headRef, end);
}

void quickSortIterative(Node** headRef) {
    if (!headRef || !*headRef || !(*headRef)->next) return;

    typedef struct {
        Node* start;
        Node* end;
    } StackItem;

    StackItem stack[100];
    int top = -1;

    Node* start = *headRef;
    Node* end = *headRef;
    while (end->next) end = end->next;

    stack[++top] = (StackItem){start, end};

    while (top >= 0) {
        StackItem current = stack[top--];
        start = current.start;
        end = current.end;

        if (!start || start == end || start == end->next)
            continue;

        Node* pivot = NULL;
        partition(start, end, &pivot);

        // Find node before pivot for left sublist
        Node* temp = start;
        Node* prev = NULL;
        while (temp != pivot && temp) {
            prev = temp;
            temp = temp->next;
        }

        if (prev && start != pivot) {
            stack[++top] = (StackItem){start, prev};
        }

        if (pivot && pivot->next && pivot->next != end->next) {
            stack[++top] = (StackItem){pivot->next, end};
        }
    }
}
