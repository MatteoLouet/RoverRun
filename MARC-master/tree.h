//
// Created by Mathis on 14/11/2024.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H

typedef struct{
    int val;
    int size;
    struct noeud **node;
    int phase;
    int chemin;
}NOEUD;

typedef struct
{
    NOEUD *racine;
}ARBRE;

ARBRE* createtree();
