//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include <stdio.h>

// Recherche l'indice d'une opération dans le tableau d'opérations en fonction de son ID.
// Retourne l'indice de l'opération si elle est trouvée, sinon retourne la taille du tableau.
int recherche(int nombre, struct Operation *operations)
{
    int i=0;
    while(nombre!=operations[i].id && i<31)
    {
        i++;
    }
    return i;
}

// Vérifie si une opération avec un certain ID est présente dans le tableau d'opérations.
// Retourne 1 si l'opération est présente, sinon retourne 0.
int est_present(int nombre,struct Operation *operations, int taille)
{
    for (int i = 0; i < taille; i++) {
        if (operations[i].id == nombre) {
            return 1;
        }
    }
    return 0;
}

// Verifie si le tableau est vide et ne contient que des 1
// Permet de savoir si l'on a fini d'attribuer toutes les opérations dans attribution_station
// Retourne 1 si toutes les opérations sont terminées, sinon retourne 0.
int fini(int* tableau,int nombre_operations)
{
    for(int i=0;i<nombre_operations;i++)
    {
        if(tableau[i]!=-1)
        {
            return 0;
        }
    }
    return 1;
}

// Vérifie l'incompatibilité entre deux opérations.
// Retourne 1 si les opérations sont incompatible, sinon retourne 0.
int incompatibilite(struct Station station,int nb,int** matrice,int j,struct Operation* operation,int nombre_operations)
{
    for(int i=0;i<j;i++)
    {
        if(est_present(station.operations[i].id,operation,nombre_operations)==1)
        {
            if(matrice[recherche(station.operations[i].id,operation)][nb]==-1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Affiche les informations du graphe de précédence, y compris le temps de cycle, les opérations et les exclusions.
void afficher_info(int **matrice_exclusion,struct Graphe_predecedence *graphe)
{
    printf("\nTEMPS DE CYCLE :\n %f \n",graphe->temps_cycle);
    printf("\nOPERATIONS : \n");
    for(int i=0;i<graphe->ordre;i++)
    {
        printf("OP: %d -> TEMPS: %f \n",graphe->operations[i].id,graphe->operations[i].temps_dexecution);
    }
    printf("\nEXCLUSION : \n");
    for(int i=0;i<graphe->ordre;i++)
    {
        for(int j=0;j<graphe->ordre;j++)
        {
            if(matrice_exclusion[i][j] == -1)
            {
                printf("%d  %d\n",graphe->operations[i].id,graphe->operations[j].id);
            }
        }
    }
    printf("\nPRECEDENCE : \n");
    for(int i=0;i<graphe->ordre;i++)
    {
        for(int j=0;j<graphe->ordre;j++)
        {
            if(graphe->matrice_adjacence[i][j]==1)
            {
                printf("%d %d\n",graphe->operations[i].id,graphe->operations[j].id);
            }
        }
    }
}

// Vérifie si une opération n'a pas de prédécesseur dans le graphe de précédence.
// Retourne le nombre de prédécesseurs de l'opération (0 si elle n'a pas de prédécesseur).
int sans_prede(struct Graphe_predecedence *graphe,int nombre)
{
    int tmp=0;
    for(int i=0;i<graphe->ordre;i++)
    {
        if(graphe->matrice_adjacence[i][nombre]==1)
        {
            tmp++;
        }
    }
    if(tmp==0)
    {
        return 0;
    }
    return tmp;
}

// Supprime une opération de la matrice d'adjacence du graphe en la marquant avec 2.
void supprimer_de_matrice(struct Graphe_predecedence *graphe,int nombre)
{
    for(int i=0;i<graphe->ordre;i++)
    {
        graphe->matrice_adjacence[i][nombre]=2;
        graphe->matrice_adjacence[nombre][i]=2;
    }
}

// Vérifie si un nombre est présent dans un tableau.
// Retourne 1 si le nombre est présent, sinon retourne 0.
int present(int* tab,int nombre,int taille)
{
    for(int i=0;i<taille;i++)
    {
        if(tab[i]==nombre)
        {
            return 1;
        }
    }
    return 0;
}

// Recherche l'ordre de découverte des opérations dans le graphe de précédence.
// Remplit le tableau ordre_decouverte avec l'ordre de découverte.
// Retourne le tableau ordre_decouverte.
int recherche_ordre_decouverte(struct Graphe_predecedence *graphe,int* ordre_decouverte) {
    int *liste_B = (int *) malloc(graphe->ordre * sizeof(int));
    int traite[graphe->ordre];
    for (int i = 0; i < graphe->ordre; i++) {
        traite[i] = i;
    }
    int y = 0;
    while (y < graphe->ordre) {
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
        for(int i=0;i<tmpB;i++)
        {

            supprimer_de_matrice(graphe, liste_B[i]);
            traite[liste_B[i]]=-1;
            ordre_decouverte[y]=liste_B[i];
            y++;
        }
    }
    return *ordre_decouverte;
}