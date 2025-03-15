#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tri.h"

// Tri par insertion - version itérative
void tri_insertion_iteratif(int tableau[], int taille) {
    int i, j, cle;
    for (i = 1; i < taille; i++) {
        cle = tableau[i];
        j = i - 1;

        while (j >= 0 && tableau[j] > cle) {
            tableau[j + 1] = tableau[j];
            j = j - 1;
        }
        tableau[j + 1] = cle;
    }
}

// Fonction auxiliaire pour le tri par insertion récursif
void tri_insertion_recursif_aux(int tableau[], int taille, int i) {
    // Cas de base: si i atteint la fin du tableau
    if (i >= taille) {
        return;
    }

    int cle = tableau[i];
    int j = i - 1;

    // Déplacer les éléments plus grands que cle
    while (j >= 0 && tableau[j] > cle) {
        tableau[j + 1] = tableau[j];
        j = j - 1;
    }
    tableau[j + 1] = cle;

    // Appel récursif pour l'élément suivant
    tri_insertion_recursif_aux(tableau, taille, i + 1);
}

// Tri par insertion - version récursive
void tri_insertion_recursif(int tableau[], int taille) {
    tri_insertion_recursif_aux(tableau, taille, 1);
}

// Fonction de fusion pour le tri fusion
void fusion(int tableau[], int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    // Tableaux temporaires
    int* gauche = malloc(n1 * sizeof(int));
    int* droite = malloc(n2 * sizeof(int));

    // Copier les données dans les tableaux temporaires
    for (i = 0; i < n1; i++)
        gauche[i] = tableau[debut + i];
    for (j = 0; j < n2; j++)
        droite[j] = tableau[milieu + 1 + j];

    // Fusionner les tableaux temporaires
    i = 0;
    j = 0;
    k = debut;
    while (i < n1 && j < n2) {
        if (gauche[i] <= droite[j]) {
            tableau[k] = gauche[i];
            i++;
        } else {
            tableau[k] = droite[j];
            j++;
        }
        k++;
    }

    // Copier les éléments restants de gauche[]
    while (i < n1) {
        tableau[k] = gauche[i];
        i++;
        k++;
    }

    // Copier les éléments restants de droite[]
    while (j < n2) {
        tableau[k] = droite[j];
        j++;
        k++;
    }

    free(gauche);
    free(droite);
}

// Fonction récursive pour le tri fusion
void tri_fusion_recursif(int tableau[], int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        // Trier les moitiés
        tri_fusion_recursif(tableau, debut, milieu);
        tri_fusion_recursif(tableau, milieu + 1, fin);

        // Fusionner les moitiés triées
        fusion(tableau, debut, milieu, fin);
    }
}

// Tri fusion - version récursive
void tri_fusion(int tableau[], int taille) {
    tri_fusion_recursif(tableau, 0, taille - 1);
}

// Tri fusion - version itérative
void tri_fusion_iteratif(int tableau[], int taille) {
    int curr_size; // Taille actuelle des sous-tableaux à fusionner
    int left_start; // Point de départ du sous-tableau gauche

    // Fusionner des sous-tableaux de taille en taille croissante
    for (curr_size = 1; curr_size <= taille - 1; curr_size = 2 * curr_size) {
        // Sélectionner le point de départ de différentes sous-tableaux de taille curr_size
        for (left_start = 0; left_start < taille - 1; left_start += 2 * curr_size) {
            // Trouver le point final du sous-tableau gauche
            int mid = left_start + curr_size - 1;
            if (mid >= taille - 1) {
                mid = taille - 1;
            }

            // Trouver le point final du sous-tableau droit
            int right_end = left_start + 2 * curr_size - 1;
            if (right_end >= taille - 1) {
                right_end = taille - 1;
            }

            // Fusionner les sous-tableaux
            if (mid < right_end) {
                fusion(tableau, left_start, mid, right_end);
            }
        }
    }
}

// Fonction de partition pour le tri rapide
int partition(int tableau[], int bas, int haut) {
    int pivot = tableau[haut]; // Pivot à la fin
    int i = (bas - 1); // Index du plus petit élément

    for (int j = bas; j <= haut - 1; j++) {
        // Si l'élément actuel est plus petit que le pivot
        if (tableau[j] < pivot) {
            i++; // Incrémenter l'index du plus petit élément
            // Échanger les éléments
            int temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
        }
    }

    // Échanger le pivot avec l'élément à la position (i + 1)
    int temp = tableau[i + 1];
    tableau[i + 1] = tableau[haut];
    tableau[haut] = temp;

    return (i + 1);
}

// Fonction auxiliaire pour le tri rapide
void tri_rapide_aux(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pi = partition(tableau, bas, haut);

        // Trier les éléments avant et après la partition
        tri_rapide_aux(tableau, bas, pi - 1);
        tri_rapide_aux(tableau, pi + 1, haut);
    }
}

// Tri rapide standard
void tri_rapide(int tableau[], int taille) {
    tri_rapide_aux(tableau, 0, taille - 1);
}

// Fonction de partition avec pivot médian pour le tri rapide
int partition_median(int tableau[], int bas, int haut) {
    int milieu = bas + (haut - bas) / 2;

    // Trouver la médiane entre bas, milieu et haut
    if (tableau[milieu] < tableau[bas]) {
        int temp = tableau[bas];
        tableau[bas] = tableau[milieu];
        tableau[milieu] = temp;
    }
    if (tableau[haut] < tableau[bas]) {
        int temp = tableau[bas];
        tableau[bas] = tableau[haut];
        tableau[haut] = temp;
    }
    if (tableau[milieu] < tableau[haut]) {
        int temp = tableau[milieu];
        tableau[milieu] = tableau[haut];
        tableau[haut] = temp;
    }

    // Maintenant le pivot (médian) est à tableau[haut]
    int pivot = tableau[haut];
    int i = bas - 1;

    for (int j = bas; j <= haut - 1; j++) {
        if (tableau[j] <= pivot) {
            i++;
            int temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
        }
    }

    int temp = tableau[i + 1];
    tableau[i + 1] = tableau[haut];
    tableau[haut] = temp;

    return i + 1;
}

// Fonction auxiliaire pour le tri rapide avec pivot médian
void tri_rapide_median_aux(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pi = partition_median(tableau, bas, haut);

        tri_rapide_median_aux(tableau, bas, pi - 1);
        tri_rapide_median_aux(tableau, pi + 1, haut);
    }
}

// Tri rapide avec pivot médian
void tri_rapide_median_wrapper(int tableau[], int taille) {
    tri_rapide_median_aux(tableau, 0, taille - 1);
}

// Fonction de partition avec pivot aléatoire pour le tri rapide
int partition_random(int tableau[], int bas, int haut) {
    // Générer un index aléatoire entre bas et haut
    int random = bas + rand() % (haut - bas + 1);

    // Échanger l'élément aléatoire avec le dernier
    int temp = tableau[random];
    tableau[random] = tableau[haut];
    tableau[haut] = temp;

    return partition(tableau, bas, haut);
}

// Fonction auxiliaire pour le tri rapide avec pivot aléatoire
void tri_rapide_random_aux(int tableau[], int bas, int haut) {
    if (bas < haut) {
        int pi = partition_random(tableau, bas, haut);

        tri_rapide_random_aux(tableau, bas, pi - 1);
        tri_rapide_random_aux(tableau, pi + 1, haut);
    }
}

// Tri rapide avec pivot aléatoire
void tri_rapide_random_wrapper(int tableau[], int taille) {
    // Initialiser le générateur de nombres aléatoires
    // Note: normalement, cela devrait être fait une seule fois au début du programme
    // srand(time(NULL));

    tri_rapide_random_aux(tableau, 0, taille - 1);
}