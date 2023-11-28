#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Structure d'un arc*/
struct Arc
{
    int numeroSommet; // numéro de numeroSommet d'un arc adjacent au numeroSommet initial
    int valeur;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un numeroSommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    int valeurSommetPrecedent;
    int distanceDuSommetInitial;
    char couleur;

};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    int sommetMax;
    pSommet* pSommet;
} Graphe;

// créer le graphe
Graphe* CreerGraphe(int ordre);


/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lireFichier(char * nomFichier);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(Graphe* graphe, int s1, int s2);

/* affichage des successeurs du numeroSommet num*/
void afficher_successeurs(pSommet * sommet, int num);

int trouverIndexSommet(Graphe* graphe, int valeur);

/*affichage du graphe avec les successeurs de chaque numeroSommet */
void graphe_afficher(Graphe* graphe);

#endif // GRAPHE_H_INCLUDED
