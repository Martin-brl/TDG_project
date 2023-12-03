//
// Created by nicol on 04/12/2023.
//
#include "header.h"
#include "def_fonctions.h"
#include <stdio.h>
#include <stdlib.h>

//Menu permettant de naviguer entre les différents algorithmes
//Fonction ne prend rien en parametre et ne renvoie rien
void menu() {
    int choix = 0;
    int charge = 0;
    do {
        int nombre_operations = 0;
        FILE *fope = fopen("/Users/keisaissaoui/CLionProjects/projet2023/operations.txt", "r");
        FILE *fexclu = fopen("/Users/keisaissaoui/CLionProjects/projet2023/exclusions.txt", "r");
        FILE *fprede = fopen("/Users/keisaissaoui/CLionProjects/projet2023/precedences.txt", "r");
        FILE *ftmp = fopen("/Users/keisaissaoui/CLionProjects/projet2023/temps_cycle.txt", "r");
        struct Operation *operations = lire_operations(fope, &nombre_operations);
        int **matrice_exclusion = (int **)malloc(nombre_operations * sizeof(int *));
        for (int i = 0; i < nombre_operations; i++) {
            matrice_exclusion[i] = (int *)malloc(nombre_operations * sizeof(int));
        }
        matrice_exclusion=lire_exclusions(fexclu, matrice_exclusion,operations);
        struct Graphe_predecedence *graphe = lire_graphe(fprede, ftmp,nombre_operations,operations);
        struct Station *station = (struct Station *)malloc(1 * sizeof(struct Station));
        station->operations=(struct Operation*)malloc(nombre_operations * sizeof(struct Operation));
        printf("\n\n     MENU      \n");
        printf(" 1. Charger Fichier\n");
        printf(" 2. Afficher informations des fichiers\n");
        printf(" 3. Optimiser la chaine d'assemblage\n");
        printf(" 4. Heuristique \n");
        printf(" 5. QUITTER\n");
        printf("\n\n\n\n");

        do {
            printf("Faites votre choix : ");
            scanf("%d", &choix);
        } while (choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);

        if (choix == 1) {
            printf("Le fichier est chargé !\n");

            charge = 1;
        }
        else if (choix == 2 && charge == 1)
        {
            afficher_info(matrice_exclusion,graphe);
        }
        else if (choix == 2 && charge != 1)
        {
            printf("Veuillez charger le fichier avant !\n");
        }
        else if (choix == 3 && charge == 1)
        {
            int choix2=0;
            do {
                printf("Le temps de cycle actuel est de : %f\n",graphe->temps_cycle);
                printf("Voulez vous le modifier ?\n");
                printf("1.OUI 2.NON :");
                scanf("%d", &choix);
            } while (choix != 1 && choix != 2);
            float tmp=0;
            if(choix==1)
            {
                do
                {
                    printf("Saisissez le temps de cycle que vous souhaitez : (Entre 1 et 100) \n");
                    scanf("%f", &tmp);
                }while(tmp<=1 || tmp>=100);
                graphe->temps_cycle=tmp;
                printf("Le nouveau temps de cycle est de : %f\n",graphe->temps_cycle);
            }
            int decouverte[graphe->ordre];
            for (int i = 0; i < graphe->ordre; i++) {
                decouverte[i]=operations[i].id;
            }
            int ordre_decouverte[graphe->ordre];
            recherche_ordre_decouverte(graphe,ordre_decouverte);
            int choix3=0;
            int tmp2=-1;
            int fini=0;
            do
            {
                printf("Choisissez les contraintes\n");
                printf(" 1. Toutes\n");
                printf(" 2. Temps De Cycle\n");
                printf(" 3. Exclusion \n");
                printf(" 4. Précédence \n");
                printf(" 0. Valider\n");
                scanf("%d", &tmp2);
                if(tmp2==0)
                {
                    fini++;
                }
                if(tmp2>=1 && tmp2<=9 && choix3<=9)
                {
                    choix3+=tmp2;
                }
            }while(fini==0 && choix3!=1 && choix3!=9);
            attribution_station(ordre_decouverte,decouverte,operations,station,graphe,matrice_exclusion,choix3);
        }
        else if (choix == 3 && charge != 1)
        {
            printf("Veuillez charger le fichier avant !\n");
        }
        else if (choix == 4 && charge == 1)
        {
            int iterations=0;
            do
            {
                printf("Choisissez le nombre d'iteration :");
                scanf("%d",&iterations);
            }while(iterations<=0);
            for(int i=0;i<iterations;i++)
            {
                printf("\nITERATION %d :\n\n",i+1);
                heuristique(graphe,station);
            }
        }
        else if (choix == 4 && charge != 1)
        {
            printf("Veuillez charger le fichier avant !\n");
        }
    } while (choix != 5);
}