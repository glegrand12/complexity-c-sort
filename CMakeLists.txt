cmake_minimum_required(VERSION 3.30)
project(dm_complexite C)

set(CMAKE_C_STANDARD 11)

add_executable(dm_complexite main.c
        Exercice1/Tri_rapide.c
        Exercice1/tri_fusion.c
        Exercice1/tri_insertion.c
        Exercice2/test_recherche.c
        count_operations.c
        array_utils.c)
