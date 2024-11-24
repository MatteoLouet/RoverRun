//
// Created by Mattéo on 14/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "loc.h"

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H


typedef struct noeud{
    int val;
    int nbFils;
    struct noeud **fils;
    int phase;
    int *chemin;
    int *mouv;
}NOEUD;

typedef struct
{
    NOEUD *racine;
}ARBRE;

ARBRE* createtree();

void remplir_tree(ARBRE *,int, int);
