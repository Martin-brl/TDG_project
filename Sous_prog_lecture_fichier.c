//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include "def_fonctions.h"
#include <stdio.h>
#include <stdlib.h>

// Lit les opérations à partir d'un fichier et retourne un tableau d'opérations.
// Met à jour le nombre d'opérations à travers le pointeur nombre_operations.
struct Operation *lire_operations(FILE *fichier, int *nombre_operations) {
    char ligne[100];
    int capacity = 1;
    struct Operation *operations = (struct Operation *)malloc(capacity * sizeof(struct Operation));
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    int id;
    float temps_execution;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (*nombre_operations >= capacity) {
            capacity *= 2;
            operations = (struct Operation *)realloc(operations, capacity * sizeof(struct Operation));
            if (operations == NULL) {
                perror("Erreur lors de la réallocation de mémoire");
                return NULL;
            }
        }
        sscanf(ligne, "%d %f", &id, &temps_execution);
        operations[*nombre_operations].id = id;
        operations[*nombre_operations].temps_dexecution = temps_execution;
        (*nombre_operations)++;
    }
    return operations;
}

// Lit les données du graphe à partir de deux fichiers et retourne un graphe de précédence.
struct Graphe_predecedence *lire_graphe(FILE *fichier1, FILE *fichier2,int nombre_operations,struct Operation *operations) {
    struct Graphe_predecedence *graphe;
    int temps_cycle, s1, s2;
    if (!fichier1) {
        printf("Erreur de lecture fichier1\n");
        exit(-1);
    }
    if (!fichier2) {
        printf("Erreur de lecture fichier2\n");
        exit(-1);
    }
    fscanf(fichier2, "%d", &temps_cycle);

    graphe = CreerGraphe(nombre_operations,operations);
    graphe->ordre=nombre_operations;
    graphe->temps_cycle = temps_cycle;
    while (fscanf(fichier1, "%d %d", &s1, &s2) != EOF)
    {
        graphe->matrice_adjacence[recherche(s1,operations)][recherche(s2,operations)]=1;
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->id_suivant = s2;
        Newarc->arc_suivant = NULL;
        pArc currentArc = graphe->operations[recherche(s1,operations)].arc;
        if (currentArc == NULL) {
            graphe->operations[recherche(s1,operations)].arc = Newarc;
        } else {
            while (currentArc->arc_suivant != NULL) {
                currentArc = currentArc->arc_suivant;
            }
            currentArc->arc_suivant = Newarc;
        }
    }

    return graphe;
}

// Lit les exclusions à partir d'un fichier et met à jour une matrice d'exclusions.
// Retourne la matrice d'exclusions mise à jour.
int** lire_exclusions(FILE *fichier, int** matrice, struct Operation *operations)
{
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int a, b;
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            matrice[i][j]=0;
        }
    }
    while (fscanf(fichier, "%d %d", &a, &b) != EOF) {
        matrice[recherche(a,operations)][recherche(b,operations)] = -1;
        matrice[recherche(b,operations)][recherche(a,operations)] = -1;
    }
    fclose(fichier);
    return matrice;
}
