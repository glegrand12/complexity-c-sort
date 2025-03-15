#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <float.h>

// Fonction de comparaison pour qsort
int comparateur(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Algorithme naïf pour trouver deux éléments x et y
void recherche_deux_elements_naif(int tableau[], int taille, int* x, int* y) {
    if (taille < 2) {
        printf("Le tableau doit contenir au moins 2 éléments\n");
        return;
    }

    // Trouver min et max
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    for (int i = 0; i < taille; i++) {
        if (tableau[i] < min_val) min_val = tableau[i];
        if (tableau[i] > max_val) max_val = tableau[i];
    }

    double cible = (max_val - min_val) / 2.0;
    double diff_min = DBL_MAX;

    for (int i = 0; i < taille; i++) {
        for (int j = i + 1; j < taille; j++) {
            double diff_actuelle = fabs((double) abs(tableau[i] - tableau[j]) - cible);
            if (diff_actuelle < diff_min) {
                diff_min = diff_actuelle;
                *x = tableau[i];
                *y = tableau[j];
            }
        }
    }
}

// Algorithme optimisé O(n log n)
void recherche_deux_elements_efficace(int tableau[], int taille, int* x, int* y) {
    if (taille < 2) {
        printf("Le tableau doit contenir au moins 2 éléments\n");
        return;
    }

    int* copie = malloc(taille * sizeof(int));
    if (!copie) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    for (int i = 0; i < taille; i++) copie[i] = tableau[i];

    qsort(copie, taille, sizeof(int), comparateur);

    int min_val = copie[0];
    int max_val = copie[taille - 1];
    double cible = (max_val - min_val) / 2.0;
    double diff_min = DBL_MAX;

    int gauche = 0, droite = 1;

    while (droite < taille) {
        double diff_actuelle = fabs(copie[droite] - copie[gauche] - cible);

        if (diff_actuelle < diff_min) {
            diff_min = diff_actuelle;
            *x = copie[gauche];
            *y = copie[droite];
        }

        if (copie[droite] - copie[gauche] < cible) {
            droite++;
        } else {
            gauche++;
            if (gauche == droite) droite++;
        }
    }

    free(copie);
}

// Test des deux algorithmes
void tester_recherche_elements() {
    int tailles[] = {100, 1000, 10000, 100000};
    int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);

    printf("=== COMPARAISON DES ALGORITHMES ===\n");
    printf("Taille\tAlgo Naïf\tAlgo Efficace\n");

    for (int i = 0; i < nb_tailles; i++) {
        int taille = tailles[i];
        int* tableau = malloc(taille * sizeof(int));

        if (!tableau) {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        for (int j = 0; j < taille; j++) tableau[j] = rand() % (taille * 10);

        int x_naif, y_naif, x_efficace, y_efficace;

        clock_t debut = clock();
        recherche_deux_elements_naif(tableau, taille, &x_naif, &y_naif);
        clock_t fin = clock();
        double temps_naif = ((double) (fin - debut)) / CLOCKS_PER_SEC;

        debut = clock();
        recherche_deux_elements_efficace(tableau, taille, &x_efficace, &y_efficace);
        fin = clock();
        double temps_efficace = ((double) (fin - debut)) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\n", taille, temps_naif, temps_efficace);

        if (i == 0) {
            printf("Résultats (taille %d):\n", taille);
            printf("Naïf: x=%d, y=%d, |x-y|=%d\n", x_naif, y_naif, abs(x_naif - y_naif));
            printf("Efficace: x=%d, y=%d, |x-y|=%d\n", x_efficace, y_efficace, abs(x_efficace - y_efficace));

            int min_val = INT_MAX, max_val = INT_MIN;
            for (int j = 0; j < taille; j++) {
                if (tableau[j] < min_val) min_val = tableau[j];
                if (tableau[j] > max_val) max_val = tableau[j];
            }
            printf("Min=%d, Max=%d, (Max-Min)/2=%.1f\n",
                   min_val, max_val, (max_val - min_val) / 2.0);
        }

        free(tableau);
    }
}
