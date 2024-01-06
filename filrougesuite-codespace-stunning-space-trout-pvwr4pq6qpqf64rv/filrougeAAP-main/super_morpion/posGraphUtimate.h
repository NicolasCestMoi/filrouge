#ifndef GRAPHU_H
#define GRAPHU_H

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

/*******Structures*********/

typedef struct{
    posGraph morpion[10]; // Le super-morpion est en fait un jeu de 10 morpions (le dernier morpion[9] est le grand morpion)
    char joueur;
}posGraphUltimate;

/******Prototypages******/

int CoupOpti(posGraph position, int parentID, int moveID, int isJoueurAuTrait, int coupopti[],int evaluation[],int ponderation);


#endif