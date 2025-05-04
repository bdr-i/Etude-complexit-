#ifndef TOUR_HANOI_H
#define TOUR_HANOI_H

#include "../pile/pile.h"

void deplacerDisque(Pile* source, Pile* destination, int id_source, int id_destination, int* compteur);
void hanoi_iteratif(Pile* source, Pile* destination, Pile* intermediaire, int n);
void hanoi_recursive(Pile* source, Pile* destination, Pile* intermediaire, int n, 
                    int id_source, int id_destination, int id_intermediaire);
#endif // TOUR_HANOI_H