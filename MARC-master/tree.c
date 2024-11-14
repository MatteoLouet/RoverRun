//
// Created by Mathis on 14/11/2024.
//
#include "tree.h"

ARBRE *create_tree(){
    ARBRE *rac = (ARBRE*)malloc(sizeof(ARBRE));
    rac->racine = (NOEUD*)malloc(sizeof(NOEUD));
    return rac;
}

void remplir_tree();