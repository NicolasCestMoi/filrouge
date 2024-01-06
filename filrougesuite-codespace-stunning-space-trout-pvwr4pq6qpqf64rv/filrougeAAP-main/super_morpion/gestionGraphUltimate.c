#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"
#include "gestionGraphUltimate.h"

void writeMorpionUltimate(posGraphUltimate positionU){
    FILE* file = fopen("morpionUlt.dot","w+");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    fprintf(file, "digraph {\n");
    fprintf(file, "  a0 [shape=none label=<<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
    fprintf(file, "    <TR>\n");

    for(int i=0; i<9;i++){
        if(i==3 || i==6){
            fprintf(file, " </TR>\n");
            fprintf(file," <TR>\n");
        }
        char couleur[10];   //Buffer qui contient la couleur du joueur

        posGraph position = positionU.morpion[i];

        if(toTab(positionU.morpion[9].pos)[i] !='.'){    //Si la position est gagnante, on rempli le morpion de la couleur

            if(toTab(positionU.morpion[9].pos)[i] == 'o') strcpy(couleur,"white");  // Le joueur 'o' correspond à couleur blanche
            else strcpy(couleur, "black");   // Le joueur 'x' correspond à couleur noire

            fprintf(file, "<TD bgcolor=\"black\">\n");
            fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"white\">\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "  </TR>\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "  </TR>\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "    <TD bgcolor=\"%s\">&nbsp;</TD>\n",couleur);
            fprintf(file, "  </TR>\n");

            fprintf(file, "</TABLE>\n");
            fprintf(file, "</TD>\n");
        }
        else{
            char* posConvert = toTab(position.pos);
            fprintf(file, "<TD bgcolor=\"black\">\n");
            fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"white\">\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[0]);
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[1]);
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[2]);
            fprintf(file, "  </TR>\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[3]);
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[4]);
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[5]);
            fprintf(file, "  </TR>\n");

            fprintf(file, "  <TR>\n");
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[6]);
            
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[7]);
            fprintf(file, "    <TD bgcolor=\"white\">%c</TD>\n",posConvert[8]);
            fprintf(file, "  </TR>\n");
            fprintf(file, "</TABLE>\n");
            fprintf(file, "</TD>\n");
            free(posConvert);
        }
    }
    fprintf(file, " </TR>\n");
    fprintf(file," </TABLE>\n");
    fprintf(file,">];\n");
    fprintf(file,"}\n");
    fclose(file);
}
