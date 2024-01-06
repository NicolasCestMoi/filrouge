#ifndef POSGRAPH_H
#define POSGRAPH_H

#define MAXLEN 100

/********Structures*******/

typedef struct posGraph {
    char pos[MAXLEN];
    char joueur;
    char last[MAXLEN];
} posGraph;


// Créer trois compartiments pour signifier le dernier coup jouer
// et le joueur -> + créer 

/******Prototypages********/

posGraph newPosition(char* c,char sigleJoueur);
char* toTab(char* position);
char* toPosGraph(char* positionC);
posGraph fenToPosGraph(char* fen);

#endif // POSGRAPH_H

