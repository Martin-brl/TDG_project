//
// Created by nicol on 26/11/2023.
//
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

struct Operation *lire_operations(FILE *fichier, int *nombre_operations) {
    char ligne[100];
    int capacity = 1;  // Initial capacity of the array
    struct Operation *operations = (struct Operation *)malloc(capacity * sizeof(struct Operation));

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    int id;
    float temps_execution;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Check if more space is needed
        if (*nombre_operations >= capacity) {
            // Double the capacity
            capacity *= 2;
            // Reallocate memory for the increased capacity
            operations = (struct Operation *)realloc(operations, capacity * sizeof(struct Operation));

            if (operations == NULL) {
                perror("Erreur lors de la réallocation de mémoire");
                return NULL;
            }
        }

        sscanf(ligne, "%d %f", &id, &temps_execution);
        operations[*nombre_operations].id = id;
        operations[*nombre_operations].temps_dexecution = temps_execution;
        printf("Opération : %d, Temps d'exécution : %f\n", operations[*nombre_operations].id, operations[*nombre_operations].temps_dexecution);
        (*nombre_operations)++;
    }

    return operations;
}

int recherche(int nombre, struct Operation *operations)
{
    int i=0;
    while(nombre!=operations[i].id && i<31)
    {
        i++;
    }
    return i;
}

struct Operation *CreerArete(struct Operation *Operations, int s1, int s2) {
    pArc Newarc = (pArc)malloc(sizeof(struct Arc));
    Newarc->id_suivant = s2;
    Newarc->arc_suivant = NULL;

    pArc currentArc = Operations[s1].arc;
    if (currentArc == NULL) {
        Operations[s1].arc = Newarc;
    } else {
        while (currentArc->arc_suivant != NULL) {
            currentArc = currentArc->arc_suivant;
        }
        currentArc->arc_suivant = Newarc;
    }
    return Operations;
}

struct Graphe_predecedence *CreerGraphe(int nombre_operations,struct Operation *operations) {
    struct Graphe_predecedence *Newgraphe = (struct Graphe_predecedence*)malloc(sizeof(struct Graphe_predecedence));
    Newgraphe->operations=(struct Operation*)malloc(nombre_operations * sizeof(struct Operation));
    Newgraphe->matrice_adj = (int **)malloc(nombre_operations * sizeof(int*));
    Newgraphe->temps_cycle=0;
    for (int i = 0; i < nombre_operations; i++) {
        Newgraphe->matrice_adj[i] = (int *)malloc(nombre_operations * sizeof(int));
        Newgraphe->operations[i] = operations[i];
    }
    for (int i = 0; i < nombre_operations; i++) {
        for (int j = 0; j < nombre_operations; j++) {
            Newgraphe->matrice_adj[i][j]=-1;
        }
    }
    return Newgraphe;

int main()
{
    printf("hello");
}