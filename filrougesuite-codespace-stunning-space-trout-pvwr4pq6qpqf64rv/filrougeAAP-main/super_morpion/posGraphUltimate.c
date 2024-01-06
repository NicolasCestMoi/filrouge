#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

#include "posGraphUtimate.h"

#define INF 1000

posGraphUltimate fenToPosGraphUltimate(char* fen){

}


int nombreDeNoeudUlt = -1;


int CoupOpti(posGraph position, int parentID, int moveID, int isJoueurAuTrait, int coupopti[], int evaluation[],int ponderation) {
    int val = -INF; // Par convention, cette valeur est -infini
    int min_eval = -INF;

    if (isNodeTerminal(position) != 0) {
        if (isNodeTerminal(position) == 2) {
            return 0;
        }
        return 100;
    } else {
        for (int i = 0; i < 9; i++) {
            char *positionConvert = toTab(position.pos);
            
            if (positionConvert[i] == '.') {
                // On copie la position actuelle dans un nouveau tableau
                char newPositionPos[9];
                strcpy(newPositionPos, positionConvert);

                // On effectue les modifications nécessaires
                newPositionPos[i] = position.joueur;

                // On créé une nouvelle structure avec le tableau modifié
                posGraph newPosition;
                strcpy(newPosition.pos, toPosGraph(newPositionPos));

                if (position.joueur == 'o') {
                    newPosition.joueur = 'x';
                } else {
                    newPosition.joueur = 'o';
                }

                if (parentID == -1) {
                    // On appelle récursivement la fonction avec la nouvelle position
                    val = max(val, -CoupOpti(newPosition, 0, nombreDeNoeudUlt, 1 - isJoueurAuTrait, coupopti, evaluation,ponderation));
                    coupopti[i] = i;
                    evaluation[i] = val;
                } else {
                    val = max(val, -CoupOpti(newPosition, moveID, nombreDeNoeudUlt, 1 - isJoueurAuTrait, coupopti, evaluation,ponderation));
                }
            }
            if (parentID == -1 && (positionConvert[i] == 'o' || positionConvert[i] == 'x')) {
                coupopti[i] = -100;
                evaluation[i] = -1000;
            }
            free(positionConvert);
        }
        return val;
    }
}
