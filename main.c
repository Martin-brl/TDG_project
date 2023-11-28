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
// tets
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

int main()
{
    printf("hello");
}