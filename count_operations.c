#include <stdio.h>
#include <stdlib.h>
#include "tri.h"
#include "count_operations.h"
#include "array_utils.h"

// Global variables for counting operations
long long compteur_comparaisons = 0;
long long compteur_echanges = 0;

// Reset counters
void reset_compteurs() {
    compteur_comparaisons = 0;
    compteur_echanges = 0;
}

// Versions instrumentées des fonctions clés

// Fonction d'échange instrumentée
void echanger_compte(int* a, int* b) {
    compteur_echanges++;
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction de comparaison instrumentée
int comparer_compte(int a, int b) {
    compteur_comparaisons++;
    return a - b;
}

// Versions instrumentées des algorithmes de tri

// Tri par insertion itératif instrumenté
void tri_insertion_iteratif_compte(int tableau[], int taille) {
    int i, j, cle;
    for (i = 1; i < taille; i++) {
        cle = tableau[i];
        j = i - 1;

        while (j >= 0 && (comparer_compte(tableau[j], cle) > 0)) {
            tableau[j + 1] = tableau[j]; // Déplacement, considéré comme un échange
            compteur_echanges++;
            j = j - 1;
        }
        tableau[j + 1] = cle;
    }
}

// Tri fusion instrumenté (seulement la fonction de fusion)
void fusion_compte(int tableau[], int debut, int milieu, int fin) {
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
        if (comparer_compte(gauche[i], droite[j]) <= 0) {
            tableau[k] = gauche[i];
            i++;
        } else {
            tableau[k] = droite[j];
            j++;
        }
        compteur_echanges++; // Comptabiliser l'affectation comme un échange
        k++;
    }

    // Copier les éléments restants de gauche[]
    while (i < n1) {
        tableau[k] = gauche[i];
        compteur_echanges++;
        i++;
        k++;
    }

    // Copier les éléments restants de droite[]
    while (j < n2) {
        tableau[k] = droite[j];
        compteur_echanges++;
        j++;
        k++;
    }

    free(gauche);
    free(droite);
}

// Tri fusion récursif instrumenté
void tri_fusion_recursif_compte(int tableau[], int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        // Trier les moitiés
        tri_fusion_recursif_compte(tableau, debut, milieu);
        tri_fusion_recursif_compte(tableau, milieu + 1, fin);

        // Fusionner les moitiés triées
        fusion_compte(tableau, debut, milieu, fin);
    }
}

// Fonction wrapper pour le tri fusion instrumenté
void tri_fusion_compte(int tableau[], int taille) {
    tri_fusion_recursif_compte(tableau, 0, taille - 1);
}

// Partition instrumentée pour le tri rapide
int partition_compte(int tableau[], int bas, int haut) {
    int pivot = tableau[haut];
    int i = (bas - 1);

    for (int j = bas; j <= haut - 1; j++) {
        if (comparer_compte(tableau[j], pivot) < 0) {
            i++;
            echanger_compte(&tableau[i], &tableau[j]);
        }
    }
    echanger_compte(&tableau[i + 1], &tableau[haut]);
    return (i + 1);
}

// Tri rapide instrumenté
void tri_rapide_compte(int tableau[], int bas, int haut) {
    int fin = 0;
    if (bas < fin) {
        int pivot = partition_compte(tableau, bas, haut);

        tri_rapide_compte(tableau, bas, pivot - 1);
        tri_rapide_compte(tableau, pivot + 1, haut);
    }
}

// Fonction wrapper pour le tri rapide instrumenté
void tri_rapide_wrapper_compte(int tableau[], int taille) {
    tri_rapide_compte(tableau, 0, taille - 1);
}


// Fonction pour tester le nombre d'opérations
void tester_operations(const char* nom_tri, void (*fonction_tri)(int[], int), int taille) {
    printf("\n=== Opérations pour %s (taille %d) ===\n", nom_tri, taille);
    printf("Type\t\tComparaisons\tÉchanges\tTotal\n");

    int* tableau = malloc(taille * sizeof(int));
    if (!tableau) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    // Test avec tableau aléatoire
    generer_tableau_aleatoire(tableau, taille);
    reset_compteurs();
    fonction_tri(tableau, taille);
    printf("Aléatoire\t%lld\t\t%lld\t\t%lld\n",
           compteur_comparaisons, compteur_echanges, compteur_comparaisons + compteur_echanges);

    // Test avec tableau trié
    generer_tableau_trie(tableau, taille);
    reset_compteurs();
    fonction_tri(tableau, taille);
    printf("Trié\t\t%lld\t\t%lld\t\t%lld\n",
           compteur_comparaisons, compteur_echanges, compteur_comparaisons + compteur_echanges);

    // Test avec tableau trié en ordre inverse
    generer_tableau_inverse(tableau, taille);
    reset_compteurs();
    fonction_tri(tableau, taille);
    printf("Inversé\t\t%lld\t\t%lld\t\t%lld\n",
           compteur_comparaisons, compteur_echanges, compteur_comparaisons + compteur_echanges);

    // Test avec tableau presque trié
    generer_tableau_presque_trie(tableau, taille);
    reset_compteurs();
    fonction_tri(tableau, taille);
    printf("Presque trié\t%lld\t\t%lld\t\t%lld\n",
           compteur_comparaisons, compteur_echanges, compteur_comparaisons + compteur_echanges);

    free(tableau);
}
