#ifndef COUNT_OPERATIONS_H
#define COUNT_OPERATIONS_H

// Function to test number of operations
void tester_operations(const char* nom_tri, void (*fonction_tri)(int[], int), int taille);

// Instrumented sorting functions
void tri_insertion_iteratif_compte(int tableau[], int taille);
void tri_fusion_compte(int tableau[], int taille);
void tri_rapide_wrapper_compte(int tableau[], int taille);

// Reset counters
void reset_compteurs();

#endif