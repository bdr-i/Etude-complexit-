
//Définition de la pile
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.h"

// Fonction pour créer une pile
Pile* creerPile() {
    Pile* pile = (Pile*)malloc(sizeof(Pile));
    if (pile == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    pile->sommet = NULL;
    return pile;
}

// Fonction pour vérifier si la pile est vide
bool estVide(Pile* pile) {
    return (pile->sommet == NULL);
}

// Fonction pour empiler un élément dans la pile
void empiler(Pile* pile, int valeur) {
    Element* nouvelElement = (Element*)malloc(sizeof(Element));
    if (nouvelElement == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouvelElement->valeur = valeur;
    nouvelElement->suivant = pile->sommet;
    pile->sommet = nouvelElement;
}

// Fonction pour dépiler un élément de la pile
int depiler(Pile* pile) {
    if (estVide(pile)) {
        fprintf(stderr, "Erreur : la pile est vide\n");
        exit(EXIT_FAILURE);
    }
    Element* elementADepiler = pile->sommet;
    int valeur = elementADepiler->valeur;
    pile->sommet = elementADepiler->suivant;
    free(elementADepiler);
    return valeur;
}

// Fonction pour obtenir la valeur du sommet de la pile sans la dépiler
int sommet(Pile* pile) {
    if (estVide(pile)) {
        fprintf(stderr, "Erreur : la pile est vide\n");
        exit(EXIT_FAILURE);
    }
    return pile->sommet->valeur;
}

// Fonction pour détruire la pile et libérer la mémoire
void detruirePile(Pile* pile) {
    while (!estVide(pile)) {
        depiler(pile);
    }
    free(pile);
}

// Fonction pour afficher le contenu de la pile (pour le débogage)
void afficherPile(Pile* pile) {
    Element* courant = pile->sommet;
    if (estVide(pile)) {
        printf("vide.");
        return;
    }
    {
        /* code */
    }
    
    while (courant != NULL) {
        printf("%d ", courant->valeur);
        courant = courant->suivant;
    }
}

