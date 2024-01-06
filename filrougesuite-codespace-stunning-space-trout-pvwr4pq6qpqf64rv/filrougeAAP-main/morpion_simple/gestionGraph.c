#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "posGraph.h"
#include "morpion.h"
#include "gestionGraph.h"

void generateDOT(posGraph position) {
    char* positionConvert = toTab(position.pos);

    printf("digraph  {\n");
    printf("  m0 [shape=none label=<<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
    //On initialise seulement la position initale 0!!
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[0]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[1]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[2]);
    printf("  </TR>\n");
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[3]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[4]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[5]);
    printf("  </TR>\n");
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[6]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[7]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[8]);
    printf("  </TR>\n");
    printf("  <TR><TD bgcolor=\"green\" colspan=\"3\">m0</TD></TR>\n");
    printf("</TABLE>>];\n");
}

void addNode(posGraph position, int parentID, int moveID,int isJoueurAuTrait){
    //On écrit dans fic le .dot
    char* positionConvert = toTab(position.pos);
    char color[10];
    if(isJoueurAuTrait == 0){
        strcpy(color,"red");
    }
    else{
        strcpy(color,"green");
    }

    printf("  m%d [shape=none label=<<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n",moveID);
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[0]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[1]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[2]);
    printf("  </TR>\n");
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[3]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[4]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[5]);
    printf("  </TR>\n");
    printf("  <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[6]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[7]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n",positionConvert[8]);
    printf("  </TR>\n");
    printf("  <TR><TD bgcolor=\"%s\" colspan=\"3\">m%d</TD></TR>\n",color,moveID);
    printf("</TABLE>>];\n");
    printf("m%d-> m%d [label=\" coup\"];\n",parentID,moveID);
    
}

void addEvaluation(int moveID,int evaluation){
    printf("m%d[xlabel = %d]\n",moveID,evaluation);
}