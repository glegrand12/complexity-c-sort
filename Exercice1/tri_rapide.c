#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour échanger deux éléments
static inline void echanger(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction de partitionnement classique
int partition(int tableau[], int bas, int haut) {
    int pivot = tableau[haut];
    int i = bas - 1;

    for (int j = bas; j < haut; j++) {
        if (tableau[j] < pivot) {
            i++;
            echanger(&tableau[i], &tableau[j]);
        }
    }
    echanger(&tableau[i + 1], &tableau[haut]);
    return i + 1;
}

// Fonction de partitionnement avec pivot médian
int partition_median_pivot(int tableau[], int bas, int haut) {
    if (haut <= bas) return bas; // Vérification pour éviter un débordement
    int milieu = bas + (haut - bas) / 2;

    // Trier bas, milieu et haut
    if (tableau[milieu] < tableau[bas]) echanger(&tableau[milieu], &tableau[bas]);
    if (tableau[haut] < tableau[bas]) echanger(&tableau[haut], &tableau[bas]);
    if (tableau[milieu] > tableau[haut]) echanger(&tableau[milieu], &tableau[haut]);

    // Mettre le pivot en position finale
    echanger(&tableau[milieu], &tableau[haut]);
    int pivot = tableau[haut];

    int i = bas - 1;
    for (int j = bas; j < haut; j++) {
        if (tableau[j] <= pivot) {
            i++;
            echanger(&tableau[i], &tableau[j]);
        }
    }

    echanger(&tableau[i + 1], &tableau[haut]);
    return i + 1;
}


// Fonction de partitionnement avec pivot aléatoire
int partition_random_pivot(int tableau[], int bas, int haut) {
    int random = bas + rand() % (haut - bas + 1);
    echanger(&tableau[random], &tableau[haut]);
    return partition(tableau, bas, haut);
}

// Tri rapide - Version classique
void tri_rapide_classique(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pivot = partition(tableau, bas, haut);
        tri_rapide_classique(tableau, bas, pivot - 1);
        tri_rapide_classique(tableau, pivot + 1, haut);
    }
}

// Tri rapide - Version avec pivot médian
void tri_rapide_median(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pivot = partition_median_pivot(tableau, bas, haut);
        tri_rapide_median(tableau, bas, pivot - 1);
        tri_rapide_median(tableau, pivot + 1, haut);
    }
}

// Tri rapide - Version avec pivot aléatoire
void tri_rapide_random(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pivot = partition_random_pivot(tableau, bas, haut);
        tri_rapide_random(tableau, bas, pivot - 1);
        tri_rapide_random(tableau, pivot + 1, haut);
    }
}

// Fonctions wrapper pour les différentes versions du tri rapide
void tri_rapide(int tableau[], int taille) {
    tri_rapide_classique(tableau, 0, taille - 1);
}

void tri_rapide_median_wrapper(int tableau[], int taille) {
    tri_rapide_median(tableau, 0, taille - 1);
}

void tri_rapide_random_wrapper(int tableau[], int taille) {
    srand(time(NULL));
    tri_rapide_random(tableau, 0, taille - 1);
}
