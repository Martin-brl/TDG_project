//
// Created by nicol on 26/11/2023.
//

#ifndef TDG_PROJECT_HEADER_H
#define TDG_PROJECT_HEADER_H

struct Operation
{
    int id;
    float temps_dexecution;
    struct Arc* arc;
};

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

#endif //TDG_PROJECT_HEADER_H
