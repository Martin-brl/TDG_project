//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include <time.h>
#include "def_fonctions.h"
#include <stdio.h>
#include <stdlib.h>

// Implémente une heuristique pour répartir les opérations dans des stations de travail.
// Modifie les structures de station passées en paramètre, ne renvoi rien.
void heuristique(struct Graphe_predecedence *graphe, struct Station *station) {
    int *liste_B = (int *) malloc(graphe->ordre * sizeof(int));
    int tmp = 0;
    int traite[graphe->ordre];
    for (int i = 0; i < graphe->ordre; i++) {
        traite[i] = i;
    }
    int a = 0;
    station = (struct Station2 *) realloc(station, (tmp + 1) * sizeof(struct Station));
    station[tmp].temps_total = 0;
    station[tmp].operations = (struct Operation *) malloc(graphe->ordre * sizeof(struct Operation));
    while (a < graphe->ordre) {
        int liste_A[graphe->ordre];
        for (int i = 0; i < graphe->ordre; i++) {
            int b = sans_prede(graphe, i);
            liste_A[i] = -1;
            if (traite[i] != -1) {
                liste_A[i] = b;
            }
        }
        int tmpB = 0;
        for (int i = 0; i < graphe->ordre; i++) {
            if (liste_A[i] == 0) {
                liste_B[tmpB] = i;
                tmpB++;
            }
        }
        int lst[tmpB];
        for (int j = 0; j < tmpB; j++) {
            lst[j] = -1;
        }

        srand(time(NULL));

        for (int j = 0; j < tmpB; j++) {
            int ale;
            do {
                ale = rand() % tmpB;
            } while (present(lst, ale, tmpB) == 1);
            lst[j] = ale;
        }
        for (int i = 0; i < tmpB; i++)
        {
            if (station[tmp].temps_total < graphe->temps_cycle)
            {
                station[tmp].operations[station[tmp].nombre_operations] = graphe->operations[lst[i]];
                station[tmp].operations[station[tmp].nombre_operations].id = 0;
                station[tmp].operations[station[tmp].nombre_operations].id = graphe->operations[liste_B[lst[i]]].id;
                station[tmp].temps_total += graphe->operations[liste_B[lst[i]]].temps_dexecution;
                supprimer_de_matrice(graphe, liste_B[lst[i]]);
                traite[liste_B[lst[i]]] = -1;
                station[tmp].nombre_operations++;
                a++;
            }
            else {
                tmp++;
                station[tmp].temps_total = 0;
                station[tmp].nombre_operations = 0;
                station[tmp].operations = (struct Operation *) malloc(graphe->ordre * sizeof(struct Operation));
            }
        }
    }
    for (int i = 0; i <= tmp; i++)
    {
        printf("STATION %d :\n", i+1);
        int j=0;
        for (int k = 0; k < station[i].nombre_operations; k++)
        {
            if(station[i].operations[k].id == 0 && station[i].operations[k].temps_dexecution==0)
            {
                j++;
            }
            else if(station[i].operations[k].id != 0 && station[i].operations[k].temps_dexecution!=0)
            {
                printf("OPERATION %d :  temps d'execution : %f\n", station[i].operations[k].id,station[i].operations[k].temps_dexecution);
            }
        }
        printf("TEMPS EXECUTION TOTAL %f : NOMBRE D'OPERATIONS %d\n\n", station[i].temps_total, station[i].nombre_operations-j);
    }
}