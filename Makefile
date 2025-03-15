CC = gcc
CFLAGS= -Wall -Wextra -O2 -std=c11 -arch arm64
LDFLAGS = -lm

# Cibles principales
all: main test_recherche

# Programme de test des algorithmes de tri
main: main.o tri_insertion.o tri_fusion.o tri_rapide.o array_utils.o count_operations.o test_recherche.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Programme de test de recherche de deux éléments
# Programme de test de recherche de deux éléments
test_recherche: test_recherche_main.o test_recherche.o array_utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_recherche_main.o: Exercice2/test_recherche_main.c Exercice2/test_recherche.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Fichiers objets pour les algorithmes de tri
tri_insertion.o: Exercice1/tri_insertion.c tri.h
	$(CC) $(CFLAGS) -c -o $@ $<

tri_fusion.o: Exercice1/tri_fusion.c tri.h
	$(CC) $(CFLAGS) -c -o $@ $<

tri_rapide.o: Exercice1/tri_rapide.c tri.h
	$(CC) $(CFLAGS) -c -o $@ $<

array_utils.o: array_utils.c array_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

count_operations.o: count_operations.c count_operations.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c tri.h array_utils.h count_operations.h Exercice2/test_recherche.h
	$(CC) $(CFLAGS) -c -o $@ $<

test_recherche.o: Exercice2/test_recherche.c Exercice2/test_recherche.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Nettoyage
clean:
	rm -f *.o test_tri test_recherche main

# Reconstruire tout
rebuild: clean all
