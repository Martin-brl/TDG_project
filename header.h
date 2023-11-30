//
// Created by nicol on 26/11/2023.
//

#ifndef TDG_PROJECT_HEADER_H
#define TDG_PROJECT_HEADER_H

typedef struct Chemin {
    int sommets[35];
    int taille;
} Chemin;

struct Arc
{
    int id_suivant; // numéro de sommet d'un arc adjacent au sommet initial
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

struct Operation
{
    int id;
    float temps_dexecution;
    struct Arc* arc;
};

/* Alias de pointeur sur un Sommet */
typedef struct Operation* pOperation;

struct Station
{
    struct Operation* operations; // Renommé pour éviter la confusion avec le type de structure
    float tmp_operation;
};

/* Alias de pointeur sur un Sommet */
typedef struct Station* pStation; // Renommé pour éviter la collision de noms

typedef enum Color {
    WHITE,
    GRAY,
    BLACK
} Color; // Defined the enum Color in the global scope

typedef struct Graphe_predecedence {
    struct Operation* operations;
    float temps_cycle;
    Color *colors;
    int** matrice_adj;
} Graphe_predecedence;

/* Alias de pointeur sur un Sommet */
typedef struct Graphe_predecedence* pGraphe_predecedence; // Renommé pour éviter la collision de noms

struct Chaine_de_production // Ajout des champs manquants
{
    int taille;
};
typedef struct Chaine_de_production* pChaine_de_production; // Renommé pour éviter la collision de noms

#endif //TDG_PROJECT_HEADER_H
