#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tour_hanoi.h"

// Prototype de la fonction récursive interne
void hanoi_rec(Pile* source, Pile* destination, Pile* intermediaire, int n,
               int id_source, int id_destination, int id_intermediaire, int* compteur);

// Déplace un disque d'une pile à une autre et incrémente le compteur
void deplacerDisque(Pile* source, Pile* destination, int id_source, int id_destination, int* compteur) {
    if (estVide(source)) {
        fprintf(stderr, "Erreur : la pile source (%d) est vide\n", id_source);
        return;
    }
    int disque = depiler(source);
    empiler(destination, disque);
    printf("Deplacer le disque %d de la tour %d a la tour %d\n", disque, id_source, id_destination);
    if (compteur != NULL) {
        (*compteur)++;
    }
}

// Version récursive principale appelée par l'utilisateur
void hanoi_recursive(Pile* source, Pile* destination, Pile* intermediaire, int n,
                     int id_source, int id_destination, int id_intermediaire) {
    int compteur = 0;
    hanoi_rec(source, destination, intermediaire, n, id_source, id_destination, id_intermediaire, &compteur);
    printf("Total de mouvements : %d\n", compteur);
}

// Fonction récursive interne
void hanoi_rec(Pile* source, Pile* destination, Pile* intermediaire, int n,
               int id_source, int id_destination, int id_intermediaire, int* compteur) {
    if (n == 0) {
        return;
    }

    hanoi_rec(source, intermediaire, destination, n - 1, id_source, id_intermediaire, id_destination, compteur);

    deplacerDisque(source, destination, id_source, id_destination, compteur);

    hanoi_rec(intermediaire, destination, source, n - 1, id_intermediaire, id_destination, id_source, compteur);
}

void hanoi_iteratif(Pile* source, Pile* destination, Pile* intermediaire, int n) {
    printf("Nombre de disques : %d\n", n);

    int compteur = 0;
    int totalMouvements = (1 << n) - 1;

    // Identifiants des tours
    int id_source = 1, id_destination = 2, id_intermediaire = 3;

    // Réorganisation des piles selon parité
    Pile* tourA = source;
    Pile* tourB = (n % 2 == 0) ? intermediaire : destination;
    Pile* tourC = (n % 2 == 0) ? destination : intermediaire;

    int idA = id_source;
    int idB = (n % 2 == 0) ? id_intermediaire : id_destination;
    int idC = (n % 2 == 0) ? id_destination : id_intermediaire;

    for (int i = 1; i <= totalMouvements; i++) {
        if (i % 3 == 1) {
            if (estVide(tourA) || (!estVide(tourB) && sommet(tourB) < sommet(tourA))) {
                deplacerDisque(tourB, tourA, idB, idA, &compteur);
            } else {
                deplacerDisque(tourA, tourB, idA, idB, &compteur);
            }
        } else if (i % 3 == 2) {
            if (estVide(tourA) || (!estVide(tourC) && sommet(tourC) < sommet(tourA))) {
                deplacerDisque(tourC, tourA, idC, idA, &compteur);
            } else {
                deplacerDisque(tourA, tourC, idA, idC, &compteur);
            }
        } else {
            if (estVide(tourB) || (!estVide(tourC) && sommet(tourC) < sommet(tourB))) {
                deplacerDisque(tourC, tourB, idC, idB, &compteur);
            } else {
                deplacerDisque(tourB, tourC, idB, idC, &compteur);
            }
        }
    }

    printf("Total de mouvements : %d\n", compteur);
}
