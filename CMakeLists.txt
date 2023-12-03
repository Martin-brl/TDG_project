cmake_minimum_required(VERSION 3.23)
project(TDG_project C)

set(CMAKE_C_STANDARD 11)

add_executable(TDG_project main.c header.h Menu.c def_fonctions.h heuristique.c sous_prog.c Sous_prog_lecture_fichier.c Sous_prog_structures.c Sous_prog_optimisation.c)
