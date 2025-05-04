#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../list/list.h"
int partition(Node* start, Node* end, Node** newPivot);
void quickSortRecursive(Node** head);
void quickSortIterative(Node** headRef);
#endif
