#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "posGraph.h"
#include "morpion.h"

void Game(posGraph position){                //Fonction qui gère la partie
    printf("Voici la position actuel : %s\n", position.pos );
    printf("La table du morpion est la suivante : \n");
    showTable(position);
    char c = 'o';        //Le premier joueur a jouer est o
    while(isNodeTerminal(position) != 1){
        Tour(&position);
    }
    if(position.joueur=='o') position.joueur='x';
    else position.joueur='o';
    printf("La partie est finie. Le vainqueur est %c\n", c);
}

void Tour(posGraph *position){                //Fonction qui gère un tour
    char* posConvert = toTab(position->pos);
    int l = 0;
    printf("Au tour de %c. Où voulez-vous jouer ? (chiffre entre 1 et 9)\n", position->joueur);
    scanf("%d", &l);                            
    while ((getchar()) != '\n');                        // On efface ce qui est écrit dans le tampon 
    if(posConvert[l-1] == '.') posConvert[l-1] = position->joueur;
    else printf("La position est déjà prise\n");
    if(position->joueur=='o') position->joueur='x';
    else position->joueur='o';
    strcpy(position->pos,toPosGraph(posConvert));
    free(posConvert);
    showTable(*position);
}

char* TourAuto(char* position,char* coup, char sigleJoueur){                //Fonction qui gère un tour
    char* position_modifiable = strdup(toTab(position));
    int l = coupToInt(coup);
    if(position_modifiable[l-1] == '.') {
        position_modifiable[l-1] = sigleJoueur;
    }
    else{
        return position;
    } 
    char* position_new = strdup(toPosGraph(position_modifiable));
    return position_new;
}

void showTable(posGraph position){
    char* posConvert = toTab(position.pos);
    char morpion[9];
    for(int i=0; i<9; i++){
        morpion[i] = posConvert[i];
        if((i + 1) % 3 == 0){
            printf("%c\n", morpion[i]);
        } else {
            printf("%c ", morpion[i]);
        }
    }
    free(posConvert);
}

int isNodeTerminal(posGraph position) {

    char* pos = toTab(position.pos); // On convertit pour simplifier la tache
    // Test des colonnes

    for (int i = 0; i < 3; i++) { // Premier cas : Trois symboles colonnes
        if (pos[i] != '.' &&
            pos[i] == pos[i + 3] &&
            pos[i] == pos[i + 6]) {
            return 1; 
        }
    }

    // Test des lignes

    for (int i = 0; i < 9; i += 3) {  // Deuxième cas : Trois symboles lignes
        if (pos[i] != '.' &&
            pos[i] == pos[i + 1] &&
            pos[i] == pos[i + 2]) {
            return 1; 
        }
    }

    // Test des diagonales

    if (pos[0] != '.' && // Diagonale de gauche à droite
        pos[0] == pos[4] &&
        pos[0] == pos[8]) {
        return 1; 
    }

    if (pos[2] != '.' && // Diagonale de droite à gauche
        pos[2] == pos[4] &&
        pos[2] == pos[6]) {
        return 1; 
    }
    int casevide = 0;
    for(int i = 0 ; i<9 ; i++){     //Cas échéant : égalité? On test les cases vides
        if(pos[i] == '.') casevide++;          //Il reste des cases  vides : on sort de la boucle
    }
    free(pos);  //Libérer la mémoire !!!! Sinon gros problème compliquer à détecter après
    if(casevide == 0) return 2;
    return 0; // Sinon, la partie continue :)
}

int coupToInt(char* coup){
    int colonne = coup[0] - 96;   // On convertit le 'a' , 'b' ou 'c' en 1,2,3 à l'aide des codes ASCII
    int ligne = coup[1]-'0';
    int position = (ligne - 1) * 3 + colonne;
    return position;
}

char* intToCoup(int position) {
    char* coup = malloc(3*sizeof(char));
    int ligne = (position - 1) / 3 + 1;
    int colonne = (position - 1) % 3 + 'a';
    sprintf(coup, "%c%d", colonne, ligne);
    return coup;
}