#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"
#include "assert.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"
#include "gestionGraphUltimate.h"

#define INFINI 1000

void GameUltimate(posGraphUltimate position){
    for(int i=0; i<9;i++){
        printf("///*****%d*******///\n",i+1);
        showTable(position.morpion[i]);
    }
    char* dernier_coup = calloc(10,sizeof(char));
    while(isNodeTerminal(position.morpion[9]) !=1){
        writeMorpionUltimate(position);
        position = TourUltimate(position,&dernier_coup);
        position.joueur = 'x';
        position = TourUltimateBot(position,&dernier_coup);
        printf("Voici le morpion principal : \n");
        showTable(position.morpion[9]);
    }
    printf("Bravo, la partie est finie et c'est : le %s qui a perdu...\n",position.joueur == 'o'? "joueur" : "bot");
}

posGraphUltimate TourUltimateBot(posGraphUltimate position, char* pointeur_last_coup[]) {
    int maximum = -INFINI;
    int grille = coupToInt(*pointeur_last_coup);
    if(isNodeTerminal(position.morpion[9]) != 0){
        return position;
    }
    if (isNodeTerminal(position.morpion[grille-1]) != 0) {
        int coupSave[9];
        int evaluationSave[9];
        CoupOpti(position.morpion[9], -1, 0, 0, coupSave, evaluationSave,0.9);
        for(int i = 0;i<9;i++){
            if(evaluationSave[i]>maximum){
                grille = coupSave[i]+1;
                maximum = evaluationSave[i];
            }
        }
    }
    maximum = -INFINI;
    int coup_a_jouer[2];
    printf("/////////////////////////////////////////////// \n Grille n° %d :\n", grille);
    showTable(position.morpion[grille - 1]);
    evaluation(position, grille, 3, 1, coup_a_jouer);
    printf("\nCoup joué par le bot: %d\n", coup_a_jouer[0]);
    strcpy(position.morpion[grille - 1].pos, TourAuto(position.morpion[grille - 1].pos, intToCoup(coup_a_jouer[0] + 1), position.joueur));

    strcpy(*pointeur_last_coup, intToCoup(coup_a_jouer[0] + 1));

    if (isNodeTerminal(position.morpion[grille - 1]) == 1) { 
        char* positionConvert = toTab(position.morpion[9].pos);
        if (position.joueur == 'o') positionConvert[grille - 1] = 'o';
        else positionConvert[grille - 1] = 'x';  
        strcpy(position.morpion[9].pos, toPosGraph(positionConvert));
        free(positionConvert);
    }

    if (position.joueur == 'o') position.joueur = 'x';
    else position.joueur = 'o';   // On échange de joueur

    for (int i = 0; i < 9; i++) {
        printf("///------%d-------///\n", i + 1);
        showTable(position.morpion[i]);
    }
    return position;
}

int evaluation(posGraphUltimate position, int coup_precedent, int horizon, int iterator, int coup_a_jouer[]) {
    int temp = -INFINI;
    int coupSave[9]={0};
    int evaluationSave[9]= {0};
    int coupSaveBigMorpion[9]={0};
    int evaluationSaveBigMorpion[9]={0};
    int maxi = -INFINI;
    
    if (iterator == horizon ) {
        CoupOpti(position.morpion[coup_precedent - 1], -1, 0, 0, coupSave, evaluationSave,0.9);
        int aux = -INFINI;
        for (int k = 0; k < 9; k++) {
            printf("eval : %d   | coup : %d\n",evaluationSave[k],coupSave[k]);
            if (evaluationSave[k] > aux && coupSave[k] != -100) { // == -100 signifie que le coup est deja pris
                coup_a_jouer[iterator - 1] = coupSave[k];
                aux = evaluationSave[k];
            }
        }
        printf("Meilleur coup fils : %d  | evaluation : %d\n", coup_a_jouer[iterator - 1], aux);
        return aux;
    }
    //if(coup_precedent==9) return -INFINI;
    else {
        int m = -INFINI;
        position.joueur = (position.joueur == 'x') ? 'o' : 'x';
        int i_max = 0;
        char grille_saved_temp[9];
        strcpy(grille_saved_temp, position.morpion[coup_precedent - 1].pos);
        showTable(position.morpion[coup_precedent - 1]);
        for (int j = 0; j < 9; j++) {
            printf("Avant\n");
            showTable(position.morpion[j]);
            strcpy(position.morpion[j].pos, TourAuto(position.morpion[j].pos, intToCoup(j + 1), position.joueur));
            printf("Après\n");
            showTable(position.morpion[j]);
            m = evaluation(position, j + 1, horizon, iterator+1, coup_a_jouer);
            CoupOpti(position.morpion[coup_precedent - 1], -1, 0, 0, coupSave, evaluationSave,0.9);
            CoupOpti(position.morpion[9], -1, 0, 0, coupSaveBigMorpion, evaluationSaveBigMorpion,0.25);
            int aux2 = -INFINI;
            int m_coup;
                
            for (int k = 0; k < 9; k++) {
                if (evaluationSave[k] > aux2  && coupSave[k] != -100) {
                    m_coup = coupSave[k] ;
                    aux2 = evaluationSave[k];
                }
            }
            printf("\n j: %d, eval: %d, m: %d, maxi: %d ", j,  evaluationSave[j], m, maxi);
            int old_maxi = maxi;
            maxi = max(maxi, m + evaluationSave[j]+evaluationSaveBigMorpion[j]);
            if (maxi > old_maxi) {
                i_max = j;
                old_maxi = maxi;
            }
            printf("\n i_max: %d, maxi: %d", i_max,  maxi);
            strcpy(position.morpion[coup_precedent - 1].pos, grille_saved_temp);
        }
        printf("\nFIN  : Grille n° : %d Joueur : %c, Coup à jouer: %d, iterator:%d _______\n", coup_precedent,position.joueur,i_max,iterator);
            //printf("\n__________________________________________\n");
        if (position.joueur == 'o') coup_a_jouer[iterator - 1] = i_max;
            
        return maxi;
    }
}

posGraphUltimate TourUltimate(posGraphUltimate position,char* pointeur_last_coup[]){
    if(strlen(*pointeur_last_coup) == 0){   // C'est le début de la partie OU on veut jouer dans un morpion fini
        printf("%c où voulez vous jouer? format[grille colonne ligne]\n",position.joueur);
        int grille;
        char colonne;
        int ligne;                                  // On utilise la convention pour un coup de la forme 'c3'
        fscanf(stdin, "%d %c %d",&grille, &colonne, &ligne);
        char coup[3];
        sprintf(coup,"%c%d",colonne,ligne);      //On écrit le coup dans le buffer 'coup' 
        if(strcmp(TourAuto(position.morpion[grille-1].pos, coup, position.joueur), position.morpion[grille-1].pos) == 0){
            printf("La position est déjà prise.\n");
            return position;
        }
        else{ 
            strcpy(position.morpion[grille-1].pos,TourAuto(position.morpion[grille-1].pos, coup, position.joueur));

            // On réalise le coup automatiquement 
            // - ATTENTION : On décale le morpion de 1 (morpion-1)

            strcpy(*pointeur_last_coup,coup);

            if(isNodeTerminal(position.morpion[grille-1]) == 1){ // Le joueur qui vient de jouer gagne la grille?
                char* positionConvert = toTab(position.morpion[9].pos);
                positionConvert[grille-1] = position.morpion[grille-1].joueur; 
                strcpy(position.morpion[9].pos,toPosGraph(positionConvert));
                free(positionConvert);
            }

            if(position.joueur == 'o') position.joueur = 'x';
            else position.joueur = 'o';   // On échange de joueur

            for(int i=0; i<9;i++){
                printf("///*****%d*******///\n",i+1);
                showTable(position.morpion[i]);
            }
            return position;
        }
    }
    else{
        int grille = coupToInt(*pointeur_last_coup);
        if(isNodeTerminal(position.morpion[grille-1]) == 1) {
            printf("Vous pouvez jouer où vous voulez !\n"); // On retourne TourUltimate avec un coup joué de taille nul (cas initial)
            strcpy(*pointeur_last_coup,"\0");
            return TourUltimate(position,pointeur_last_coup);
        }
        printf("%c où voulez vous jouer dans la grille %d? format[grille colonne ligne]\n",position.joueur,grille);
        int buffer;     //On utilise un buffer pour stocker la grille mais on ne s'en sert pas
        char colonne;
        int ligne;          // On utilise la convention pour un coup de la forme 'c3'
        fscanf(stdin, "%d %c %d", &buffer, &colonne, &ligne);
        char coup[3];
        sprintf(coup,"%c%d",colonne,ligne);      //On écrit le coup dans le buffer 'coup' 
        if(strcmp(TourAuto(position.morpion[grille-1].pos, coup, position.joueur), position.morpion[grille-1].pos) == 0){
            printf("La position est déjà prise.\n");
            return position;
        }
        else{ 
            strcpy(*pointeur_last_coup,coup);
            strcpy(position.morpion[grille-1].pos,TourAuto(position.morpion[grille-1].pos, coup, position.joueur)); 

            // On réalise le coup automatiquement 
            // - ATTENTION : On décale le morpion de 1 (morpion-1)

            if(isNodeTerminal(position.morpion[grille-1]) == 1){ // Le joueur qui vient de jouer gagne la grille?
                char* positionConvert = toTab(position.morpion[9].pos);
                positionConvert[grille-1] = position.morpion[grille-1].joueur; 
                strcpy(position.morpion[9].pos,toPosGraph(positionConvert));
                free(positionConvert);
            }

            if(position.joueur == 'o') position.joueur = 'x';
            else position.joueur = 'o';   // On échange de joueur

            for(int i=0; i<9;i++){
                printf("///*****%d*******///\n",i+1);
                showTable(position.morpion[i]);
            }
            return position;
        }
    }
}
