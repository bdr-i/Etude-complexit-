#ifndef PILE_H
#define PILE_H

#include <stdbool.h>

// Définition de la structure pour un élément de la pile
typedef struct Element {
    int valeur;
    struct Element* suivant;
} Element;

// Définition de la structure pour la pile
typedef struct Pile {
    Element* sommet;
} Pile;

// Prototypes des fonctions pour manipuler la pile
Pile* creerPile();
bool estVide(Pile* pile);
void empiler(Pile* pile, int valeur);
int depiler(Pile* pile);
int sommet(Pile* pile);
void detruirePile(Pile* pile);
void afficherPile(Pile* pile);

#endif // PILE_H