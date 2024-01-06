#ifndef GRAPH_H
#define GRAPH_H

#include "morpion.h"
#include "posGraph.h"

/******Structures*******/

typedef struct {
    posGraph position;
    int parentID;  // ID du parent
    int moveID;    // ID du mouvement
} DecisionTreeNode;

/*****Prototypages******/

void generateDOT(posGraph position);
void addNode(posGraph position, int parentID, int moveID,int isJoueurAuTrait);
void addEvaluation(int moveID,int evaluation);

#endif // GRAPH_H
