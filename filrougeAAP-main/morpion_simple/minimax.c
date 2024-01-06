#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minimax.h"
#include "posGraph.h"
#include "gestionGraph.h"
#include "morpion.h"

int nombreDeNoeud = -1;

int decisionTree(posGraph position, int parentID, int moveID, int isJoueurAuTrait) {
    int val = -10000; //Par convention, cette valeur est -infini
    if(parentID==-1) nombreDeNoeud++;       //On traite le cas particulier du premier coup
    nombreDeNoeud++;  
    if (isNodeTerminal(position) != 0) {
        if(isNodeTerminal(position) == 2) {
            addEvaluation(moveID,0);
            return 0;
        }
        addEvaluation(moveID,-100);
        return -100;
    } else {
        for (int i = 0; i < 9; i++) {
            char* positionConvert = toTab(position.pos);
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
                    addNode(newPosition, 0, nombreDeNoeud,1-isJoueurAuTrait);
                    val = max(val,-decisionTree(newPosition, 0, nombreDeNoeud,1-isJoueurAuTrait));
                } else{ 
                    addNode(newPosition, moveID, nombreDeNoeud, 1-isJoueurAuTrait);
                    val = max(val, -decisionTree(newPosition, moveID, nombreDeNoeud,1-isJoueurAuTrait));
                    
                }
            }
            free(positionConvert);
        }
        addEvaluation(moveID, val);
        return val;
    }
}

void makeDecisionTree(posGraph position){
    generateDOT(position);  //Génération du .dot
    decisionTree(position,-1,0,1);    //Lancement récursif de l'arbre de décision avec un parentID = -1 (convention)
    /***Fermeture du document*/ 
    FILE* fic = stdout;
    fprintf(fic, "}");
    fclose(fic);
}

int max(int a, int b){
    if(a>=b) return a;
    return b;
}