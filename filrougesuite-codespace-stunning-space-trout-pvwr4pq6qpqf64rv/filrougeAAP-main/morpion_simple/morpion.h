#ifndef MORPION_H
#define MORPION_H

#include "posGraph.h"

/*****Prototypages******/

void Game(posGraph position);
int isNodeTerminal(posGraph position);
void showTable(posGraph position);
void Tour(posGraph * position);
char* TourAuto(char* position,char* coup, char sigleJoueur);
int coupToInt(char* coup);
char* intToCoup( int);

#endif // MORPION_H
