#ifndef SMORPION_H
#define SMORPION_H

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

#include "posGraphUtimate.h"

/********Prototypages*********/

void GameUltimate(posGraphUltimate position);
posGraphUltimate TourUltimate(posGraphUltimate position, char* last_coup[]);
posGraphUltimate TourUltimateBot(posGraphUltimate position, char* pointeur_last_coup[]);
int evaluation(posGraphUltimate position,int coup_precedent, int horizon,int iterator, int coup_a_jouer[], int Joueurautrait);

#endif