#include <stdio.h>
// Tri par insertion - Version itérative
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

// Tri par insertion - Version récursive
void tri_insertion_recursif(int tableau[], int taille) {
    if (taille <= 1)
        return;

    tri_insertion_recursif(tableau, taille - 1);

    int dernier = tableau[taille - 1];
    int j = taille - 2;

    while (j >= 0 && tableau[j] > dernier) {
        tableau[j + 1] = tableau[j];
        j--;
    }
    tableau[j + 1] = dernier;
}