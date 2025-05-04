#include <stdlib.h>
#include <stdio.h>
#include "merge_sort.h"

// Fusionne deux sous-listes de positions p à q et q+1 à o
void fusion(Node** head, int p, int q, int o) {
    int n1 = q - p + 1;
    int n2 = o - q;

    int* left = (int*)malloc(n1 * sizeof(int));
    int* right = (int*)malloc(n2 * sizeof(int));

    if (!left || !right) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }

    Node* temp = *head;
    int index = 0;

    // Aller jusqu'à l'élément d'indice p
    while (index < p && temp != NULL) {
        temp = temp->next;
        index++;
    }

    // Copier les éléments dans left[]
    for (int i = 0; i < n1 && temp != NULL; i++) {
        left[i] = temp->data;
        temp = temp->next;
    }

    // Copier les éléments dans right[]
    for (int i = 0; i < n2 && temp != NULL; i++) {
        right[i] = temp->data;
        temp = temp->next;
    }

    // Revenir à l'élément d'indice p pour fusionner dans la liste
    temp = *head;
    index = 0;
    while (index < p && temp != NULL) {
        temp = temp->next;
        index++;
    }

    int i = 0, j = 0;

    // Fusionner left[] et right[] dans la liste chaînée
    while (i < n1 && j < n2 && temp != NULL) {
        if (left[i] <= right[j]) {
            temp->data = left[i++];
        } else {
            temp->data = right[j++];
        }
        temp = temp->next;
    }

    // Ajouter le reste de left[]
    while (i < n1 && temp != NULL) {
        temp->data = left[i++];
        temp = temp->next;
    }

    // Ajouter le reste de right[]
    while (j < n2 && temp != NULL) {
        temp->data = right[j++];
        temp = temp->next;
    }

    free(left);
    free(right);
}

void mergeSortRecursive(Node** head, int p, int o) {
    if (p < o) {
        int q = (p + o) / 2; 
        mergeSortRecursive(head, p, q);
        mergeSortRecursive(head, q + 1, o);
        fusion(head, p, q, o);
    }
}

int tailleListe(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}


Node* fusionListes(Node* gauche, Node* droite, int tailleG, int tailleD, Node** finFusion) {
    Node newList;
    Node* current = &newList;
    newList.next = NULL;

    while (tailleG > 0 && tailleD > 0) {
        if (gauche->data <= droite->data) {
            current->next = gauche;
            gauche = gauche->next;
            tailleG--;
        } else {
            current->next = droite;
            droite = droite->next;
            tailleD--;
        }
        current = current->next;
    }

    while (tailleG-- > 0) {
        current->next = gauche;
        gauche = gauche->next;
        current = current->next;
    }

    while (tailleD-- > 0) {
        current->next = droite;
        droite = droite->next;
        current = current->next;
    }

    *finFusion = current;  
    return newList.next;    
}
void mergeSortIterative(Node** head, int n) {
    if (!head || !*head || n < 2) return;

    for (int tailleBloc = 1; tailleBloc < n; tailleBloc *= 2) {
        Node* current = *head;
        Node* prevTail = NULL;
        Node* newHead = NULL;

        while (current) {
            // 1. Séparer gauche
            Node* gauche = current;
            int tailleG = 0;
            Node* gaucheFin = NULL;

            for (tailleG = 0; tailleG < tailleBloc && current; tailleG++) {
                gaucheFin = current;
                current = current->next;
            }

            if (gaucheFin) gaucheFin->next = NULL;  // couper gauche

            // 2. Séparer droite
            Node* droite = current;
            int tailleD = 0;
            Node* droiteFin = NULL;

            for (tailleD = 0; tailleD < tailleBloc && current; tailleD++) {
                droiteFin = current;
                current = current->next;
            }

            if (droiteFin) droiteFin->next = NULL;  // couper droite

             // Fusionner les blocs
             Node* finFusion = NULL;
             Node* fusionnee = fusionListes(gauche, droite, tailleG, tailleD, &finFusion);
 
             if (!newHead)
                 newHead = fusionnee;
             else
                 prevTail->next = fusionnee;
 
             prevTail = finFusion;
             if (prevTail)
                 prevTail->next = current;
         }
 
         *head = newHead;  // Mettre à jour la tête
     }
 }