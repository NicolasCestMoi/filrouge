#ifndef GGRAPHU_H
#define GGRAPHU_H

#include "../morpion_simple/posGraph.h"
#include "../morpion_simple/morpion.h"
#include "../morpion_simple/gestionGraph.h"
#include "../morpion_simple/minimax.h"

#include "posGraphUtimate.h"
#include "morpion_to_S.h"

void writeDotTable(posGraph position, char* filename);
void writeMorpionUltimate(posGraphUltimate positionU);

#endif