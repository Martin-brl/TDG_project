#include <stdio.h>
#include <stdlib.h>
#ifndef PROJET2023_HEADER_H
#define PROJET2023_HEADER_H

// Structure représentant un arc reliant deux opérations dans le graphe de précédence.
struct Arc
{
    int id_suivant;           // ID de l'opération suivante dans l'arc.
    struct Arc* arc_suivant;  // Pointeur vers l'arc suivant dans la liste d'arcs.
};

// Pointeur vers une structure Arc, utilisé pour simplifier la syntaxe.
typedef struct Arc* pArc;

// Structure représentant une opération dans le graphe de précédence.
struct Operation
{
    int id;                        // Identifiant unique de l'opération.
    float temps_dexecution;        // Temps d'exécution de l'opération.
    struct Arc* arc;               // Liste d'arcs reliant cette opération à d'autres.
};

// Structure représentant une station de travail.
struct Station
{
    struct Operation* operations;  // Tableau d'opérations associées à la station.
    float temps_total;             // Temps total d'exécution des opérations dans la station.
    int nombre_operations;         // Nombre d'opérations actuellement dans la station.
};

// Structure représentant le graphe de précédence des opérations.
typedef struct Graphe_predecedence
{
    int** matrice_adjacence;       // Matrice d'adjacence pour représenter les relations entre les opérations.
    int ordre;                     // Nombre total d'opérations dans le graphe.
    struct Operation* operations;  // Tableau d'opérations dans le graphe.
    float temps_cycle;             // Temps total nécessaire pour compléter un cycle dans le graphe.
} Graphe_predecedence;

#endif //PROJET2023_HEADER_H