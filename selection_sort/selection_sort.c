#include "selection_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include "../list/list.h"

void selectionSort(Node** head) {
    Node* current = *head;
    Node* index = NULL;

    if (current == NULL) return;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->data > index->data) {
                swap(current, index);
            }
            index = index->next;
        }
        current = current->next;
    }
}
int trouverMinIndex(Node* head, int start, int n) {
    Node* current = head;

    // Aller jusqu'à l'index 'start'
    for (int i = 0; i < start; i++) {
        current = current->next;
    }

    int minIndex = start;
    int minValue = current->data;

    // Continuer à parcourir la liste à partir de 'start'
    for (int i = start; i < n; i++) {
        if (current->data < minValue) {
            minValue = current->data;
            minIndex = i;
        }
        current = current->next;
    }
    return minIndex;
}

void SortRecursive(Node** head, int start, int n) {
    if (*head == NULL) return; // Liste vide
    if (start >= n - 1) {
        return; // Base : liste triée
    }

    int minIndex = trouverMinIndex(*head, start, n);

    Node* minNode = *head;
    Node* current = *head;

    for (int i = 0; i < start; i++) {
        current = current->next;
    }
    for (int i = 0; i < minIndex; i++) {
        minNode = minNode->next;
    }

    // La condition sert a ne pas désordonner la liste si le minimum est déjà à la bonne place
    if(minNode != current) {
        swap(minNode, current); // Échange les données
    }

    SortRecursive(head, start + 1, n); // Tri récursif sur le reste
}


void selectionSortRecursive(Node** head) {
    if (*head == NULL) return; // Liste vide
    int n = 0;
    Node* current = *head;
    while (current != NULL) {
        n++;
        current = current->next;
    }
    SortRecursive(head, 0, n);
}
