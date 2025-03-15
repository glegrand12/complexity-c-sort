#ifndef TRI_H
#define TRI_H

// Fonctions de tri par insertion
void tri_insertion_iteratif(int tableau[], int taille);
void tri_insertion_recursif(int tableau[], int taille);
void tri_insertion_iteratif_compte(int* tableau, int taille);

// Fonctions de tri fusion
void fusion(int tableau[], int debut, int milieu, int fin);
void tri_fusion_recursif(int tableau[], int debut, int fin);
void tri_fusion_iteratif(int tableau[], int taille);
void tri_fusion(int tableau[], int taille);
void tri_fusion_compte(int* tableau, int taille);

// Fonctions de tri rapide
void echanger(int* a, int* b);
int partition(int tableau[], int bas, int haut);
int partition_median_pivot(int tableau[], int bas, int haut);
int partition_random_pivot(int tableau[], int bas, int haut);
void tri_rapide_classique(int tableau[], int bas, int haut);
void tri_rapide_median(int tableau[], int bas, int haut);
void tri_rapide_random(int tableau[], int bas, int haut);
void tri_rapide(int tableau[], int taille);
void tri_rapide_median_wrapper(int tableau[], int taille);
void tri_rapide_random_wrapper(int tableau[], int taille);
void tri_rapide_wrapper_compte(int* tableau, int taille);

void tester_operations(const char* nom_tri, void (*fonction_tri)(int[], int), int taille);
#endif /* TRI_H */