#include <stdlib.h>
#include "array_utils.h"

void generer_tableau_aleatoire(int tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        tableau[i] = rand() % (taille * 10);
    }
}

void generer_tableau_trie(int tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        tableau[i] = i;
    }
}

void generer_tableau_inverse(int tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        tableau[i] = taille - i - 1;
    }
}

void generer_tableau_presque_trie(int tableau[], int taille) {
    generer_tableau_trie(tableau, taille);

    // Perturber environ 10% des éléments
    int nb_perturbations = taille / 10;
    for (int i = 0; i < nb_perturbations; i++) {
        int index1 = rand() % taille;
        int index2 = rand() % taille;
        int temp = tableau[index1];
        tableau[index1] = tableau[index2];
        tableau[index2] = temp;
    }
}

int est_trie(int tableau[], int taille) {
    for (int i = 1; i < taille; i++) {
        if (tableau[i-1] > tableau[i]) {
            return 0; // Non trié
        }
    }
    return 1; // Trié
}

void copier_tableau(int source[], int destination[], int taille) {
    for (int i = 0; i < taille; i++) {
        destination[i] = source[i];
    }
}

