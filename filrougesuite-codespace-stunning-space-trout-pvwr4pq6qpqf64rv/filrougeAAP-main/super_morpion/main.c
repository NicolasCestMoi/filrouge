#include <stdio.h>
#include <stdlib.h>

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"
#include "gestionGraphUltimate.h"

int main(){
    posGraphUltimate position;
    position.joueur = 'o'; // Il faut initialisé le joueur qui commence (à automatiser)
    for(int j=0;j<9;j++){
        position.morpion[j] = newPosition("9",'o');
        showTable(position.morpion[j]);
    }
    position.morpion[9] = newPosition("9",'o');
    GameUltimate(position);

    //int coup_a_jouer[2];
    //position.joueur = 'x';
    //evaluation(position,7, 2,1, coup_a_jouer);

    //printf("%d %d",coup_a_jouer[0],coup_a_jouer[1]);

}