#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tri.h"
#include "Exercice2/test_recherche.h"
#include <math.h>
#include "array_utils.h"


// Fonction pour mesurer le temps d'exécution d'un algorithme de tri
double mesurer_temps(void (*fonction_tri)(int[], int), int tableau[], int taille) {
    int* copie = malloc(taille * sizeof(int));
    if (!copie) {
        printf("Erreur d'allocation mémoire\n");
        return -1;
    }

    // Copier le tableau pour préserver l'original
    copier_tableau(tableau, copie, taille);

    const clock_t debut = clock();
    fonction_tri(copie, taille);
    const clock_t fin = clock();

    const double temps = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    // Vérifier que le tri a fonctionné
    if (!est_trie(copie, taille)) {
        printf("ERREUR: Le tri n'a pas fonctionné correctement!\n");
    }

    free(copie);
    return temps;
}


void executer_tests_operations() {
    srand(time(NULL));

    const int tailles[] = {1000, 5000, 10000};

    printf("=== ANALYSE DU NOMBRE D'OPÉRATIONS ===\n");

    for (size_t i = 0; i < sizeof(tailles) / sizeof(tailles[0]); i++) {
        const int taille = tailles[i];

        printf("\n==== TAILLE: %d ====\n", taille);

        tester_operations("Tri par insertion", tri_insertion_iteratif_compte, taille);
        tester_operations("Tri fusion", tri_fusion_compte, taille);
        tester_operations("Tri rapide", tri_rapide_wrapper_compte, taille);
    }
}

// Structure pour stocker les résultats de temps
typedef struct {
    double aleatoire;
    double trie;
    double inverse;
    double presque_trie;
} ResultatTemps;

// Fonction principale
/*
#include <stdio.h>
#include "tri.h"
#include "array_utils.h"

// Liste des tris à tester
void (*tris[])(int[], int) = {
    tri_insertion_iteratif,
    tri_insertion_recursif,
    tri_fusion,
    tri_fusion_iteratif,
    tri_rapide,
    tri_rapide_median_wrapper,
    tri_rapide_random_wrapper
};

// Noms des tris correspondants
const char* noms_tris[] = {
    "Tri Insertion Itératif",
    "Tri Insertion Récursif",
    "Tri Fusion",
    "Tri Fusion Itératif",
    "Tri Rapide Classique",
    "Tri Rapide (Pivot Médian)",
    "Tri Rapide (Pivot Aléatoire)"
};

#define NB_TRIS (sizeof(tris) / sizeof(tris[0]))

void tester_un_tri(void (*fonction_tri)(int[], int), const char* nom) {
    int tableau[] = {5, 1, 3, 2, 4};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    printf("\n=== Test de %s ===\n", nom);
    printf("Avant tri : ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    fonction_tri(tableau, taille);

    printf("Après tri : ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    if (!est_trie(tableau, taille)) {
        printf("❌ ERREUR : Le tri %s ne fonctionne pas correctement !\n", nom);
    } else {
        printf("✅ OK : Le tri %s fonctionne.\n", nom);
    }
}

int main() {
    for (int i = 0; i < NB_TRIS; i++) {
        tester_un_tri(tris[i], noms_tris[i]);
    }
    return 0;
}
*/


int main() {
    srand(time(NULL));

    // Tailles de tableaux à tester
    const int tailles[] = {1000, 5000, 10000, 20000};
    const int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);

    // Tableau de fonctions de tri
    void (*fonctions_tri[])(int[], int) = {
        tri_insertion_iteratif,
        tri_insertion_recursif,
        tri_fusion,
        tri_fusion_iteratif,
        tri_rapide,
        tri_rapide_median_wrapper,
        tri_rapide_random_wrapper
    };

    // Noms des fonctions de tri
    const char* noms_tri[] = {
        "Tri par insertion itératif",
        "Tri par insertion récursif",
        "Tri fusion récursif",
        "Tri fusion itératif",
        "Tri rapide classique",
        "Tri rapide (pivot médian)",
        "Tri rapide (pivot aléatoire)"
    };

    int nb_algos = sizeof(fonctions_tri) / sizeof(fonctions_tri[0]);

    // Tableau pour stocker les résultats
    ResultatTemps** resultats = malloc(nb_algos * sizeof(ResultatTemps*));
    for (int i = 0; i < nb_algos; i++) {
        resultats[i] = malloc(nb_tailles * sizeof(ResultatTemps));
    }

    // Effectuer les tests
    for (int t = 0; t < nb_tailles; t++) {
        int taille = tailles[t];
        printf("Test pour taille %d en cours...\n", taille);

        int* tableau_aleatoire = malloc(taille * sizeof(int));
        int* tableau_trie = malloc(taille * sizeof(int));
        int* tableau_inverse = malloc(taille * sizeof(int));
        int* tableau_presque_trie = malloc(taille * sizeof(int));

        // Générer les différents types de tableaux
        generer_tableau_aleatoire(tableau_aleatoire, taille);
        generer_tableau_trie(tableau_trie, taille);
        generer_tableau_inverse(tableau_inverse, taille);
        generer_tableau_presque_trie(tableau_presque_trie, taille);

        // Tester chaque algorithme
        for (int a = 0; a < nb_algos; a++) {
            // Cas défavorable: tableau inverse pour tri par insertion, aléatoire pour les autres
            if (a < 2) { // Tri par insertion
                resultats[a][t].inverse = mesurer_temps(fonctions_tri[a], tableau_inverse, taille);
            } else {
                resultats[a][t].aleatoire = mesurer_temps(fonctions_tri[a], tableau_aleatoire, taille);
            }

            // Cas favorable: tableau trié
            resultats[a][t].trie = mesurer_temps(fonctions_tri[a], tableau_trie, taille);

            // Cas moyen: tableau presque trié
            resultats[a][t].presque_trie = mesurer_temps(fonctions_tri[a], tableau_presque_trie, taille);
        }

        free(tableau_aleatoire);
        free(tableau_trie);
        free(tableau_inverse);
        free(tableau_presque_trie);
    }

    // Afficher les résultats
    printf("\n===== RÉSULTATS DES TESTS =====\n");

    for (int a = 0; a < nb_algos; a++) {
        printf("\n%s\n", noms_tri[a]);
        printf("Taille\tCas favorable\tCas défavorable\tCas moyen\n");

        for (int t = 0; t < nb_tailles; t++) {
            printf("%d\t%.6f\t", tailles[t], resultats[a][t].trie);

            // Cas défavorable dépend de l'algorithme
            if (a < 2) { // Tri par insertion
                printf("%.6f\t", resultats[a][t].inverse);
            } else {
                printf("%.6f\t", resultats[a][t].aleatoire);
            }

            printf("%.6f\n", resultats[a][t].presque_trie);
        }
    }

    // Libérer la mémoire
    for (int i = 0; i < nb_algos; i++) {
        free(resultats[i]);
    }
    free(resultats);

    // Effectuer le test de l'exercice 2
    printf("\n===== TEST DE L'EXERCICE 2 =====\n");

    int tailles_ex2[] = {100, 1000, 10000, 100000};
    int nb_tailles_ex2 = sizeof(tailles_ex2) / sizeof(tailles_ex2[0]);

    printf("Taille\tAlgo naïf (s)\tAlgo efficace (s)\tRapport\n");

    for (int i = 0; i < nb_tailles_ex2; i++) {
        int taille = tailles_ex2[i];
        int* tableau = malloc(taille * sizeof(int));

        // Générer un tableau aléatoire
        generer_tableau_aleatoire(tableau, taille);

        int x_naif, y_naif;
        int x_efficace, y_efficace;

        // Mesurer le temps pour l'algorithme naïf
        clock_t debut = clock();
        recherche_deux_elements_naif(tableau, taille, &x_naif, &y_naif);
        clock_t fin = clock();
        double temps_naif = ((double) (fin - debut)) / CLOCKS_PER_SEC;

        // Mesurer le temps pour l'algorithme efficace
        debut = clock();
        recherche_deux_elements_efficace(tableau, taille, &x_efficace, &y_efficace);
        fin = clock();
        double temps_efficace = ((double) (fin - debut)) / CLOCKS_PER_SEC;

        // Calculer le rapport de performance
        double rapport = temps_naif / temps_efficace;

        printf("%d\t%.6f\t%.6f\t%.2f\n", taille, temps_naif, temps_efficace, rapport);

        free(tableau);
    }
    executer_tests_operations();
    return 0;
}