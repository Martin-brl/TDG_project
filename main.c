#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graphe.h"

Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    Newgraphe->ordre = ordre;
    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

void couleursDesSommets(Graphe* graphe){
    for (int i = 0; i < graphe->ordre; ++i) {
        printf("couleur du sommet %d : %c\n", graphe->pSommet[i]->valeur, graphe->pSommet[i]->couleur);
    }
}


void initPreBfs(Graphe* graphe){
    for (int i = 0; i < graphe->ordre; ++i) {
        graphe->pSommet[i]->couleur = 'B';
    }
}

void copyColors(Graphe* graphe, char* couleurs){
    for (int i = 0; i < graphe->ordre; ++i) {
        couleurs[i] = graphe->pSommet[i]->couleur;
    }
}

int* findUnprecededVertexes(Graphe* graphe){
    pSommet sommetActuel;
    pArc arcActuel;
    int* sommetsNonPrecedes;
    int sommetPrecede = 0;
    int nombreDeSommetsNonPrecedes = 0;
    for (int i = 0; i < graphe->ordre; ++i) {
        for (int j = 0; j < graphe->ordre; ++j) {
            sommetPrecede = 0;
            sommetActuel = graphe->pSommet[i];
            arcActuel = sommetActuel->arc;
            while (arcActuel != NULL){
                if (graphe->pSommet[arcActuel->numeroSommet]->valeur == sommetActuel->valeur){
                    sommetPrecede ++;
                }
                arcActuel = arcActuel->arc_suivant;
            }
        }
        if (sommetPrecede == 0){
            nombreDeSommetsNonPrecedes ++;
        }
    }
    sommetsNonPrecedes = malloc(nombreDeSommetsNonPrecedes * sizeof(int));
    for (int i = 0; i < graphe->ordre; ++i) {
        for (int j = 0; j < graphe->ordre; ++j) {
            sommetPrecede = 0;
            sommetActuel = graphe->pSommet[i];
            arcActuel = sommetActuel->arc;
            printf("sommets decouverts depuis %d : \n", sommetActuel->valeur);
            while (arcActuel != NULL){
                if (graphe->pSommet[arcActuel->numeroSommet]->valeur == sommetActuel->valeur){
                    sommetPrecede ++;
                }
                arcActuel = arcActuel->arc_suivant;
            }

        }
        if (sommetPrecede == 0){
            sommetsNonPrecedes[i] = graphe->pSommet[i]->valeur;
        }
    }
    return sommetsNonPrecedes;
}

int checkIfBelongs(Graphe* graphe, int* discoveryOrder, int numberToFind){
    for (int i = 0; i < graphe->ordre; ++i) {
        if (discoveryOrder[i] == numberToFind){
            return 1;
        }
    }
    return 0;
}

int* bfs(Graphe* graphe, int sommetInitial, int* discoveryOrder, int numberOfDiscoveredVertex){
    printf("\nBEGINNING BFS PROGRAM\n\n");
    //printf("sommet initial du bfs : %d\n", sommetInitial);
    pSommet sommetActuel = graphe->pSommet[sommetInitial];
    sommetActuel->couleur = 'G';
    discoveryOrder[numberOfDiscoveredVertex] = graphe->pSommet[sommetInitial]->valeur;
    numberOfDiscoveredVertex ++;
    pArc arcActuel;
    char* couleurs = malloc(graphe->ordre * sizeof(char));
    int graphNonConnexe = 1;
    int parcoursComplete = 0;
    while(parcoursComplete < graphe->ordre && graphNonConnexe){
        graphNonConnexe = 0;
        //printf("parcoursComplete : %d\ngraphNonConnexe : %d\n\n", parcoursComplete, graphNonConnexe);
        //printf("beginning while loop 1\n");
        parcoursComplete = 0;
        for (int i = 0; i < graphe->ordre; ++i) {
            if (graphe->pSommet[i]->couleur == 'N'){
                parcoursComplete++;
            }
        }

        copyColors(graphe, couleurs);

        for (int i = 0; i < graphe->ordre; ++i) {
            if (couleurs[i] == 'G'){
                sommetActuel = graphe->pSommet[i];
                arcActuel = sommetActuel->arc;
                if (arcActuel != NULL && !checkIfBelongs(graphe, discoveryOrder, arcActuel->numeroSommet)){
                    printf("\nsommets decouverts depuis %d : \n", sommetActuel->valeur);
                }
                while (arcActuel != NULL){
                    if (graphe->pSommet[trouverIndexSommet(graphe, arcActuel->numeroSommet)]->couleur == 'B'){
                        graphe->pSommet[trouverIndexSommet(graphe, arcActuel->numeroSommet)]->couleur = 'G';
                        printf("%d, ", arcActuel->numeroSommet);
                        discoveryOrder[numberOfDiscoveredVertex] = arcActuel->numeroSommet;
                        numberOfDiscoveredVertex ++;
                        graphNonConnexe++;
                    }
                    arcActuel = arcActuel->arc_suivant;
                }
                sommetActuel->couleur = 'N';
                //printf("sommet %d explore\n\n", sommetActuel->valeur);
            }
        }
    }
    //couleursDesSommets(graphe);
    for (int i = 0; i < graphe->ordre; ++i) {
        if (graphe->pSommet[i]->couleur == 'B'){
            bfs(graphe, i, discoveryOrder, numberOfDiscoveredVertex);
        }
    }
    return discoveryOrder;
}


int trouverIndexSommet(Graphe* graphe, int valeur) {
    for (int i = 0; i < graphe->sommetMax; i++) {
        if (graphe->pSommet[i]->valeur == valeur) {
            return i;
        }
    }
    return -1;
}

pSommet* CreerArete(Graphe* graphe, int s1, int s2) {
    int indexS1 = trouverIndexSommet(graphe, s1);
    int indexS2 = trouverIndexSommet(graphe, s2);
    //printf("Le sommet %d a pour valeur %d\n", indexS1, s1);
    //printf("Le sommet %d a pour valeur %d\n", indexS2, s2);
    if (indexS1 == -1 || indexS2 == -1) {
        printf("Erreur : Sommet non trouve.\n");
        return NULL;
    }

    if (graphe->pSommet[indexS1]->arc == NULL) {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->numeroSommet = s2;
        Newarc->arc_suivant = NULL;
        graphe->pSommet[indexS1]->arc = Newarc;
        return graphe->pSommet;
    } else {
        pArc temp = graphe->pSommet[indexS1]->arc;
        while (temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->numeroSommet = s2;
        Newarc->arc_suivant = NULL;
        if (temp->numeroSommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->numeroSommet = temp->numeroSommet;
            temp->numeroSommet = s2;
            temp->arc_suivant = Newarc;
            return graphe->pSommet;
        }

        temp->arc_suivant = Newarc;
        return graphe->pSommet;
    }
}


void afficher_successeurs(pSommet * sommet, int num){

    printf("Sommet %d :\n",sommet[num]->valeur);

    pArc arc = sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("%d ",arc->numeroSommet);
        arc = arc->arc_suivant;
    }
}

void afficherGraphe(Graphe* graphe)
{
    printf("graphe\n");
    if(!graphe->orientation) printf("pas_oriente\n");
    else printf("oriente\n");
    printf("ordre = %d\n",graphe->ordre);
    printf("listes d'adjacence :\n");
    for (int i=0; i < graphe->ordre; i++){
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }
}

Graphe * lireFichier(char * nomFichier){
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int s1, s2;
    int taille = 0;
    int noeuds[100] = {0};
    int noeudMax = -1;

    if (!ifs){
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }


    while (fscanf(ifs,"%d%d", &s1, &s2) != EOF){
        noeuds[s1] = 1;
        noeuds[s2] = 1;
        if (s1 > noeudMax) noeudMax = s1;
        if (s2 > noeudMax) noeudMax = s2;
        taille++;
    }

    int ordre = 0;

    for(int i = 0; i <= noeudMax; i++) {
        if(noeuds[i]) ordre++;
    }
    printf("ordre : %d\n", ordre);
    graphe = CreerGraphe(ordre);
    graphe->sommetMax = noeudMax;

    ordre = 0;
    for(int i = 0; i <= noeudMax; i++) {
        if(noeuds[i]){
            graphe->pSommet[ordre]->valeur = i;
            ordre++;
        }
    }
    rewind(ifs);

    int i = 0;
    while (fscanf(ifs,"%d%d", &s1, &s2) != EOF) {
        //printf("%dieme arete :%d, de rang %d----------vers %d, de rang %d\n\n", i, s1, trouverSommet(graphe, s1), s2, trouverIndexSommet(graphe, s2));
        graphe->pSommet = CreerArete(graphe, s1, s2);
        i++;
    }

    printf("end\n");

    fclose(ifs);

    graphe->taille = taille;
    printf("ordre = %d, taille = %d\n", graphe->ordre, graphe->taille);

    return graphe;
}

int main() {
    Graphe* graphe = lireFichier("precedences.txt");
    initPreBfs(graphe);
    int* discoveryOrder = malloc(graphe->ordre * sizeof(int));
    bfs(graphe, 0, discoveryOrder, 0);
    return 0;
}