//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include "def_fonctions.h"
#include <stdio.h>
#include <stdlib.h>

//Permet d'optimiser la ligne d'assemblage et attribue toutes les opérations a n stations en fonctions des contraintes choisies
void attribution_station(int* ordre_decouverte,int* decouverte, struct Operation* operations, struct Station* station, struct Graphe_predecedence* graphe, int** matrice,int choix)
{
    int i = 0;
    if(choix==1 || choix==9)//full
    {
        while (fini(ordre_decouverte, graphe->ordre) != 1) {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if(((station[i].temps_total)+0.5) < graphe->temps_cycle)
                {
                    if (ordre_decouverte[j] != -1)
                    {
                        if(station[i].nombre_operations==0)
                        {
                            station[i].operations[station[i].nombre_operations].id=0;
                        }
                        if(incompatibilite(station[i], ordre_decouverte[j], matrice, station[i].nombre_operations, operations,graphe->ordre)==0)
                        {
                            station[i].operations[station[i].nombre_operations] = operations[ordre_decouverte[j]];
                            station[i].operations[station[i].nombre_operations].id = operations[ordre_decouverte[j]].id;
                            station[i].temps_total += operations[ordre_decouverte[j]].temps_dexecution;
                            ordre_decouverte[j]=-1;
                            station[i].nombre_operations++;
                        }
                    }
                }
            }
            i++;
        }
    }
    if(choix==2)//temps
    {
        while (fini(decouverte, graphe->ordre) != 1) {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if(station[i].temps_total < graphe->temps_cycle)
                {
                    if(decouverte[j] != -1)
                    {
                        if(station[i].nombre_operations == 0)
                        {
                            station[i].operations[station[i].nombre_operations].id = 0;
                        }
                        station[i].operations[station[i].nombre_operations] = operations[j];
                        station[i].operations[station[i].nombre_operations].id = operations[j].id;
                        station[i].temps_total += operations[j].temps_dexecution;
                        decouverte[j]=-1;
                        station[i].nombre_operations++;
                    }
                }
            }
            i++;
        }
    }
    if(choix==3)//exclu
    {
        while (fini(decouverte, graphe->ordre) != 1) {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if (decouverte[j] != -1)
                {
                    if (station[i].nombre_operations == 0) {
                        station[i].operations[station[i].nombre_operations].id = 0;
                    }
                    if (incompatibilite(station[i], j, matrice, station[i].nombre_operations, operations, graphe->ordre) == 0) {
                        station[i].operations[station[i].nombre_operations] = operations[j];
                        station[i].operations[station[i].nombre_operations].id = operations[j].id;
                        station[i].temps_total += operations[j].temps_dexecution;
                        decouverte[j]=-1;
                        station[i].nombre_operations++;
                    }
                }
            }
            i++;
        }
    }
    if(choix==4)//précédence
    {
        while (fini(ordre_decouverte, graphe->ordre) != 1) {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if (ordre_decouverte[j] != -1)
                {
                    if(station[i].nombre_operations==0)
                    {
                        station[i].operations[station[i].nombre_operations].id=0;
                    }
                    station[i].operations[station[i].nombre_operations] = operations[ordre_decouverte[j]];
                    station[i].operations[station[i].nombre_operations].id = operations[ordre_decouverte[j]].id;
                    station[i].temps_total += operations[j].temps_dexecution;
                    ordre_decouverte[j]=-1;
                    station[i].nombre_operations++;
                }
            }
            i++;
        }
    }
    if(choix==5)//temps + exclu
    {
        while (fini(decouverte, graphe->ordre) != 1)
        {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if(((station[i].temps_total)+0.5) < graphe->temps_cycle)
                {
                    if (decouverte[j] != -1)
                    {
                        if(station[i].nombre_operations==0)
                        {
                            station[i].operations[station[i].nombre_operations].id=0;
                        }
                        if(incompatibilite(station[i], j, matrice, station[i].nombre_operations, operations,graphe->ordre)==0)
                        {
                            station[i].operations[station[i].nombre_operations] = operations[j];
                            station[i].operations[station[i].nombre_operations].id = operations[j].id;
                            station[i].temps_total += operations[j].temps_dexecution;
                            decouverte[j]=-1;
                            station[i].nombre_operations++;
                        }
                    }
                }
            }
            i++;
        }
    }
    if(choix==6)//temps + précédence
    {
        while (fini(ordre_decouverte, graphe->ordre) != 1)
        {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if(((station[i].temps_total)+0.5) < graphe->temps_cycle)
                {
                    if (ordre_decouverte[j] != -1)
                    {
                        if(station[i].nombre_operations==0)
                        {
                            station[i].operations[station[i].nombre_operations].id=0;
                        }
                        station[i].operations[station[i].nombre_operations] = operations[ordre_decouverte[j]];
                        station[i].operations[station[i].nombre_operations].id = operations[ordre_decouverte[j]].id;
                        station[i].temps_total += operations[ordre_decouverte[j]].temps_dexecution;
                        ordre_decouverte[j]=-1;
                        station[i].nombre_operations++;
                    }
                }
            }
            i++;
        }
    }
    if(choix==7)//exclu + précédence
    {
        while (fini(ordre_decouverte, graphe->ordre) != 1) {
            station = (struct Station*)realloc(station, (i + 1) * sizeof(struct Station));
            station[i].temps_total = 0;
            station[i].temps_total=0;
            station[i].operations = (struct Operation*)malloc(graphe->ordre * sizeof(struct Operation));
            for(int j=0;j<graphe->ordre;j++)
            {
                if (ordre_decouverte[j] != -1)
                {
                    if(station[i].nombre_operations==0)
                    {
                        station[i].operations[station[i].nombre_operations].id=0;
                    }
                    if(incompatibilite(station[i], ordre_decouverte[j], matrice, station[i].nombre_operations, operations,graphe->ordre)==0)
                    {
                        station[i].operations[station[i].nombre_operations] = operations[ordre_decouverte[j]];
                        station[i].operations[station[i].nombre_operations].id = operations[ordre_decouverte[j]].id;
                        station[i].temps_total += operations[j].temps_dexecution;
                        ordre_decouverte[j]=-1;
                        station[i].nombre_operations++;
                    }
                }
            }
            i++;
        }
    }
    for(int y=0;y<i;y++)
    {
        printf("STATION %d :\n", y+1);
        for (int k = 0; k < station[y].nombre_operations; k++)
        {
            printf("OPERATION %d :  temps d'execution %f\n", station[y].operations[k].id, station[y].operations[k].temps_dexecution);
        }
        printf("TEMPS D'EXECUTION TOTAL : %f NOMBRE D'OPERATION : %d \n \n", station[y].temps_total, station[y].nombre_operations);
    }
}