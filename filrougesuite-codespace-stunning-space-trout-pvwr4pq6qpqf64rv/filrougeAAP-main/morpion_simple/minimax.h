#ifndef MINIMAX_H
#define MINIMAX_H

#include "morpion.h"
#include "posGraph.h"
#include "gestionGraph.h"

/*****Prototypages******/

int decisionTree(posGraph position,int parentID,int moveID,int isJoueurAuTrait);
void makeDecisionTree(posGraph);
int max(int,int);
#endif // MINIMAX_H
