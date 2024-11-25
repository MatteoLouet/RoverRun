//
// Created by Mathis on 14/11/2024.
//
#include "tree.h"
#include "map.h"

ARBRE *createtree(){
    ARBRE *rac = (ARBRE*)malloc(sizeof(ARBRE));
    rac->racine = (NOEUD*)malloc(sizeof(NOEUD));
    return rac;
}

int *supp_mouv(int *mouv, int nb_mouv, int val){
    int *new_mouv = (int *)malloc((nb_mouv-1)*sizeof(int));
    int i=0, j=0;
    while (i < nb_mouv)
    {
        if (mouv[i]!=val)
        {
            new_mouv[j] = mouv[i];
            j++;
        }
        i++;
    }
    return new_mouv;
}


NOEUD *creer_noeud(int value, int nb_fils,int phase,int *mouv, int nb_mouv, t_localisation loc, t_map map)
{

    NOEUD *new_noeud;
    new_noeud = (NOEUD *)malloc(sizeof(NOEUD));
    new_noeud->val = value;
    new_noeud->phase = phase;
    new_noeud->nbFils = nb_fils;
    new_noeud->fils = (NOEUD **)malloc(nb_fils*sizeof(NOEUD *));
    new_noeud->mouv = mouv;
    new_noeud->loc = loc;


    if (nb_mouv > phase) {
        for (int i = 0; i < nb_fils; i++) {

            t_move moves = mouv[i];
            t_localisation new_loc = move(loc, moves);


            if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)){

                int new_value = map.costs[new_loc.pos.y][new_loc.pos.x];

                if (new_value < 10000) {

                    printf("%d   ",new_value);

                    new_noeud->fils[i] = creer_noeud(new_value, nb_fils - 1, phase + 1,
                                                     supp_mouv(mouv, nb_fils, mouv[i]), nb_mouv, new_loc, map);
                }
                else {
                    printf("C  ");
                }
            }
            else{
                printf("P  ");
            }
        }
        printf("\n");
    }
    return new_noeud;
}


void remplir_tree(ARBRE *tree, int parmi, int nb_mouv, t_localisation loc, t_map map)
{

    int *mouv = (int *)malloc(parmi*sizeof(int));
    for (int i = 0; i < parmi; i++){
        mouv[i] = i;
    }

    int val = map.costs[loc.pos.y][loc.pos.x];
    printf("%d\n",val);
    tree->racine = creer_noeud(val, parmi, 0, mouv, nb_mouv, loc, map);

}

