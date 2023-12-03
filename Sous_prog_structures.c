//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

// Crée et initialise un nouveau graphe de précédence avec le nombre d'opérations et le tableau d'opérations donnés.
// Alloue dynamiquement l'espace mémoire nécessaire pour le graphe et sa matrice d'adjacence.
// Initialise la matrice d'adjacence à zéro et copie les opérations dans le graphe.
struct Graphe_predecedence *CreerGraphe(int nombre_operations,struct Operation *operations) {
    struct Graphe_predecedence *Newgraphe = (struct Graphe_predecedence*)malloc(sizeof(struct Graphe_predecedence));
    Newgraphe->operations=(struct Operation*)malloc(nombre_operations * sizeof(struct Operation));
    Newgraphe->matrice_adjacence=(int**)malloc(nombre_operations * sizeof(int*));
    for (int i = 0; i < nombre_operations; i++)
    {
        Newgraphe->matrice_adjacence[i]=(int*)malloc(nombre_operations * sizeof(int));
        for (int j = 0; j < nombre_operations; j++)
        {
            Newgraphe->matrice_adjacence[i][j]=0;
        }
    }
    Newgraphe->temps_cycle=0;
    Newgraphe->ordre=0;
    for (int i = 0; i < nombre_operations; i++)
    {
        Newgraphe->operations[i] = operations[i];
    }
    return Newgraphe;
}

// Initialise une station avec un tableau d'opérations vides.
// Alloue dynamiquement l'espace mémoire nécessaire pour la station et ses opérations.
struct Station* init_station(struct Station*station,int nombre_operations)
{
    struct Station* NewStation = (struct Station*)malloc(nombre_operations*sizeof(struct Station));
    for(int i=0;i<nombre_operations;i++)
    {
        NewStation[i].operations=(struct Operation*)malloc(nombre_operations * sizeof(struct Operation));
        for(int j=0;j<nombre_operations;j++)
        {
            NewStation[i].operations[j].id=0;
            NewStation[i].operations[j].temps_dexecution=0;
            NewStation[i].operations[j].arc=NULL;
        }
    }
    return NewStation;
}