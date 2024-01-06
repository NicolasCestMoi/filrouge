all : supermorpion.exe

supermorpion.exe : main.c morpion_to_S.c gestionGraphUltimate.c posGraphUltimate.c ../morpion_simple/gestionGraph.c ../morpion_simple/posGraph.c ../morpion_simple/minimax.c ../morpion_simple/morpion.c
	gcc main.c morpion_to_S.c posGraphUltimate.c gestionGraphUltimate.c ../morpion_simple/gestionGraph.c ../morpion_simple/morpion.c ../morpion_simple/minimax.c ../morpion_simple/posGraph.c -o supermorpion.exe