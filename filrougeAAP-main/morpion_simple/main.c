#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "posGraph.h"
#include "morpion.h"
#include "gestionGraph.h"
#include "minimax.h"

int main(int argc, char* argv[]){
  /**********Vérification du FEN****************/
  assert(argc==2);
  /***Génération du .dot et arbre de décision***/

  makeDecisionTree(fenToPosGraph(argv[1]));
}
