#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list/list.h"
#include "selection_sort/selection_sort.h"
#include "merge_sort/merge_sort.h"
#include "quick_sort/quick_sort.h"
#include "tour_hanoi/tour_hanoi.h"
#include "pile/pile.h"

// Afficher les trois tours
void afficherLesTours(Pile* source, Pile* destination, Pile* intermediaire) {
    printf("\n\n----------- etat des tours --------------------\n");
    printf("Pile source : ");
    afficherPile(source);
    printf("\nPile intermediaire : ");
    afficherPile(intermediaire);
    printf("\nPile destination : ");
    afficherPile(destination);
    printf("\n----------------------------------------------\n\n");
}

// Choix de methode Hanoi
int choisirMethodeHanoi(const char* message) {
    int choix;
    printf("\n----------- Choix de la methode de Hanoi ----------------\n");
    printf("1. %s iterative\n", message);
    printf("2. %s recursive\n", message);
    printf("Choix : ");
    scanf("%d", &choix);

    while (choix != 1 && choix != 2) {
        printf("Choix invalide. Choisissez 1 ou 2 : ");
        scanf("%d", &choix);
    }
    return choix;
}

// Choix de methode de tri
int choisirMethodeDeTri(const char* message) {
    int choix;
    printf("\n----------- Choix de la methode de tri -------------------\n");
    printf("1. Tri par %s iteratif\n", message);
    printf("2. Tri par %s recursif\n", message);
    printf("Choix : ");
    scanf("%d", &choix);

    while (choix != 1 && choix != 2) {
        printf("Choix invalide. Choisissez 1 ou 2 : ");
        scanf("%d", &choix);
    }
    return choix;
}

int main() {
    Node* head = NULL;
    srand(time(NULL));
    int taille;
    int isRunning = 1;

    while (isRunning) {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1. Generer une liste chainee\n");
        printf("2. Trier la liste par selection\n");
        printf("3. Trier la liste par fusion\n");
        printf("4. Trier la liste par tri rapide\n");
        printf("5. Resoudre le probleme de Hanoi\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");

        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                freeList(head);
                head = NULL;
                printf("Entrez la taille de la liste (0 à 100000) : ");
                scanf("%d", &taille);
                while (taille < 0 || taille > 100000) {
                    printf("Taille invalide. Reessayez : ");
                    scanf("%d", &taille);
                }
                for (int i = 0; i < taille; i++) {
                    insertAtEnd(&head, rand() % 8);
                }
                printf("Liste generee :\n");
                printList(head);
                break;
            }

            case 2: {
                if (!head) {
                    printf("Liste vide. Generez d'abord une liste.\n");
                    break;
                }
                int choixTri = choisirMethodeDeTri("selection");
                printf("Liste avant tri :\n");
                printList(head);

                clock_t start = clock();
                if (choixTri == 1)
                    selectionSort(&head);
                else
                    selectionSortRecursive(&head);
                clock_t end = clock();

                printf("Liste triee :\n");
                printList(head);
                printf("Temps d'execution : %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }

            case 3: {
                if (!head) {
                    printf("Liste vide. Generez d'abord une liste.\n");
                    break;
                }
                int choixTri = choisirMethodeDeTri("fusion");
                printf("Liste avant tri :\n");
                printList(head);

                clock_t start = clock();
                if (choixTri == 1)
                    mergeSortIterative(&head, taille);
                else
                    mergeSortRecursive(&head, 0, taille - 1);
                clock_t end = clock();

                printf("Liste triee :\n");
                printList(head);
                printf("Temps d'execution : %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }

            case 4: {
                if (!head) {
                    printf("Liste vide. Generez d'abord une liste.\n");
                    break;
                }
                int choixTri = choisirMethodeDeTri("tri rapide");
                printf("Liste avant tri :\n");
                printList(head);

                clock_t start = clock();
                if (choixTri == 1)
                    quickSortIterative(&head);
                else
                    quickSortRecursive(&head);
                clock_t end = clock();

                printf("Liste triee :\n");
                printList(head);
                printf("Temps d'execution : %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                break;
            }

            case 5: {
                int n;
                printf("Nombre de disques : ");
                scanf("%d", &n);
                while (n < 1 || n > 32) {
                    printf("Nombre invalide. Reessayez : ");
                    scanf("%d", &n);
                }

                Pile* source = creerPile();
                Pile* destination = creerPile();
                Pile* intermediaire = creerPile();

                for (int i = n; i >= 1; i--) {
                    empiler(source, i);
                }

                afficherLesTours(source, destination, intermediaire);

                int methode = choisirMethodeHanoi("Hanoi");
                clock_t start = clock();
                if (methode == 1)
                    hanoi_iteratif(source, destination, intermediaire, n);
                else
                    hanoi_recursive(source, destination, intermediaire, n, 1, 2, 3);
                clock_t end = clock();
                printf("Temps d'execution : %.3f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
                afficherLesTours(source, destination, intermediaire);

                detruirePile(source);
                detruirePile(destination);
                detruirePile(intermediaire);
                break;
            }

            case 6:
                isRunning = 0;
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }

    freeList(head);
    return 0;
}
