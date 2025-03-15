// Fonction de fusion pour le tri fusion
void fusion(int tableau[], int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    // Tableaux temporaires
    int gauche[n1], droite[n2];

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
}

// Tri fusion - Version récursive
void tri_fusion_recursif(int tableau[], int debut, int fin) {
    if (debut < fin) {
        const int milieu = debut + (fin - debut) / 2;

        // Trier les moitiés
        tri_fusion_recursif(tableau, debut, milieu);
        tri_fusion_recursif(tableau, milieu + 1, fin);

        // Fusionner les moitiés triées
        fusion(tableau, debut, milieu, fin);
    }
}

// Tri fusion - Version itérative
void tri_fusion_iteratif(int tableau[], int taille) {
    int debut;

    // Commencer par fusionner des sous-tableaux de taille 1
    for (int taille_courante = 1; taille_courante < taille; taille_courante = 2 * taille_courante) {
        // Parcourir le tableau avec des pas de taille_courante*2
        for (debut = 0; debut < taille - 1; debut += 2 * taille_courante) {
            // Trouver le point du milieu
            int milieu = (debut + taille_courante - 1 < taille - 1) ?
                         (debut + taille_courante - 1) : (taille - 1);

            // Trouver le point de fin pour la fusion actuelle
            int fin = (debut + 2 * taille_courante - 1 < taille - 1) ?
                     (debut + 2 * taille_courante - 1) : (taille - 1);

            // Fusionner les sous-tableaux
            fusion(tableau, debut, milieu, fin);
        }
    }
}

// Fonction wrapper pour le tri fusion récursif
void tri_fusion(int tableau[], int taille) {
    tri_fusion_recursif(tableau, 0, taille - 1);
}