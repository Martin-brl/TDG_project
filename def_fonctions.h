//
// Created by nicol on 04/12/2023.
//

#ifndef TDG_PROJECT_DEF_FONCTIONS_H
#define TDG_PROJECT_DEF_FONCTIONS_H

//
// Created by keis aissaoui on 12/11/2023.
//
#include <stdio.h>
#include <stdlib.h>



struct Operation *lire_operations(FILE *fichier, int *nombre_operations);
int recherche(int nombre, struct Operation *operations);
struct Graphe_predecedence *CreerGraphe(int nombre_operations,struct Operation *operations);
struct Graphe_predecedence *lire_graphe(FILE *fichier1, FILE *fichier2,int nombre_operations,struct Operation *operations);
int est_present(int nombre,struct Operation *operations, int taille);
int fini(int* tableau,int nombre_operations);
int** lire_exclusions(FILE *fichier, int** matrice, struct Operation *operations);
int incompatibilite(struct Station station,int nb,int** matrice,int j,struct Operation* operation,int nombre_operations);
void attribution_station(int* ordre_decouverte,int* decouverte, struct Operation* operations, struct Station* station, struct Graphe_predecedence* graphe, int** matrice,int choix);
void afficher_info(int **matrice_exclusion,struct Graphe_predecedence *graphe);
void heuristique(struct Graphe_predecedence *graphe,struct Station* station);
int present(int* tab,int nombre,int taille);
void supprimer_de_matrice(struct Graphe_predecedence *graphe,int nombre);
int sans_prede(struct Graphe_predecedence *graphe,int nombre);
void recherche_ordre_decouverte(struct Graphe_predecedence *graphe,int* ordre_decouverte);
void menu();




#endif //TDG_PROJECT_DEF_FONCTIONS_H
