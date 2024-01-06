#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "posGraph.h"
#include "morpion.h"

posGraph fenToPosGraph(char* fen) {
    posGraph position;
    int i = 0;

    char tempPos[100];          //On passe par une chaine* auxilliaire pour éviter les erreurs d'alloc dynamique

    while (fen[i] != ' ') {
        tempPos[i] = fen[i];
        i++;
    }
    
    tempPos[i] = '\0'; 
    strcpy(position.pos, tempPos);     

    position.joueur = fen[i + 1];

    return position;
}

posGraph newPosition(char* pos,char sigleJoueur){
    posGraph position;
    strcpy(position.pos, pos);
    position.joueur = sigleJoueur;
    return position;
}

char* toTab(char* pos){
        /*Fonction qui doit convertir une position 
        en position directe, i.e. : 
        o2xoox2
        -> o..xoox..*/
    char* positionConvert = malloc(sizeof(char)*10);
    int decalage = 0;
    int aux=0;
    for(int i = 0; i < strlen(pos); i++) {         // Ici, on convertit (conversion facile mais chiante)
        if(pos[i] == 'x' || pos[i] == 'o') {
            positionConvert[i + decalage] = pos[i];
        }
        else {
            for(int j = 0; j < (pos[i] - '0'); j++) {
                positionConvert[i + decalage] = '.';
                decalage++;
            }
            decalage--;             // A la fin, on est parti une fois trop loin (faite le test) donc on enlève 1 au décalage
        }
    }
    positionConvert[strlen(pos) + decalage] = '\0'; //On ajoute le caractère nul en fin de chaîne
    return positionConvert;
}

char* toPosGraph(char* positionC) {
    char* pos = malloc(sizeof(char)*MAXLEN);
    int index = 0;
    int i = 0;

    while (i < strlen(positionC)) {
        if (positionC[i] == '.') {
            int j = 0;
            while (positionC[i + j] == '.') {
                j++;
            }

            pos[index++] = '0' + j; // Convertir le nombre d'emplacements vides en caractère
            i += j;
        } else {
            pos[index++] = positionC[i++];
        }
    }
    pos[index++] = '\0';
    return pos;
}