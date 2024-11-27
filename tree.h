//
// Created by Mathis on 14/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "map.h"
#include "queue.h"


#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H


typedef struct noeud{
    int val;
    int nbFils;
    struct noeud **fils;
    int phase;
    t_queue_int chemin;
    int *mouv;
    t_localisation loc;
}NOEUD;





// Définition de la structure t_queue pour une file de NOEUD
typedef struct s_list_noeud {
    NOEUD **values; // Tableau dynamique pour stocker les nœuds
    int nbElts;
    int size;      // Taille maximale de la file
} t_list_noeud;





typedef struct
{
    NOEUD *racine;
    t_list_noeud feuille;
}ARBRE;

ARBRE* createtree();

void remplir_tree(ARBRE *,int, int, t_localisation, t_map);





t_list_noeud createList(int size);

void ajoute_noeud(t_list_noeud *, NOEUD *);



NOEUD* trouver_min(ARBRE *);

void deplacement(t_localisation *, int, t_queue_int);

void guidage_MARC(t_localisation, t_map);
