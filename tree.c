//
// Created by Mathis on 14/11/2024.
//
#include <assert.h>
#include <time.h>
#include "tree.h"
#include "map.h"

ARBRE *createtree(){
    ARBRE *rac = (ARBRE*)malloc(sizeof(ARBRE));
    rac->racine = (NOEUD*)malloc(sizeof(NOEUD));
    return rac;
}

t_list_noeud createList(int size){
    assert(size > 0);
    t_list_noeud t_list;
    t_list.size = size;
    t_list.nbElts = 0;
    t_list.values = (NOEUD **)malloc(size * sizeof(NOEUD *));
    return t_list;
}


void ajoute_noeud(t_list_noeud *t_list, NOEUD *value){
    assert(t_list->nbElts < t_list->size);
    t_list->values[t_list->nbElts] = value;
    t_list->nbElts++;
}




int random_int()
{
    int random = rand() % 100;


    if (random < 22) {
        return 0;
    }
    else if (random < 37) {
        return 1;
    }
    else if (random < 44) {
        return 2;
    }
    else if (random < 51) {
        return 3;
    }
    else if (random < 72) {
        return 4;
    }
    else if (random < 93) {
        return 5;
    }
    else {
        return 6;
    }
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


NOEUD *creer_noeud(int value, int nb_fils,int phase,int *mouv, int nb_mouv, t_queue_int chemin, t_localisation loc, t_map map, ARBRE *tree)
{

    NOEUD *new_noeud;
    new_noeud = (NOEUD *)malloc(sizeof(NOEUD));
    new_noeud->val = value;
    new_noeud->phase = phase;
    new_noeud->nbFils = nb_fils;
    new_noeud->fils = (NOEUD **)malloc(nb_fils*sizeof(NOEUD *));
    new_noeud->mouv = mouv;
    new_noeud->loc = loc;
    new_noeud->chemin = chemin;

    printf("%d   ", new_noeud->val);

    if (new_noeud->val != 0) {

        if (nb_mouv > phase) {

            if (map.soils[loc.pos.y][loc.pos.x] == 3) {
                nb_fils = 4;
            }


            for (int i = 0; i < nb_fils; i++) {



                t_move moves = mouv[i];

                if (map.soils[loc.pos.y][loc.pos.x] == 2) {
                    switch (moves){
                        case F_10:
                            moves = -1;
                            break;
                        case F_20:
                            moves = F_10;
                            break;
                        case F_30:
                            moves = F_20;
                            break;
                        case B_10:
                            moves = -1;
                            break;
                        case T_LEFT:
                            moves = -1;
                            break;
                        case T_RIGHT:
                            moves = -1;
                            break;
                        case U_TURN:
                            srand(time(NULL));
                            int random = rand();
                            if (random % 2 == 0){
                                moves = T_RIGHT;
                            }
                            else{
                                moves = T_LEFT;
                            }
                            break;
                        default:
                            break;

                    }
                }

                t_localisation new_loc = move(loc, moves);
                //printf("%d  ",moves);

                if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {

                    int new_value = map.costs[new_loc.pos.y][new_loc.pos.x];

                    if (new_value < 10000) {

                        t_queue_int new_chemin = createQueueint(nb_mouv);
                        for (int j = 0; j < (chemin.last - chemin.first); j++) {
                            new_chemin.values[j] = chemin.values[chemin.first + j];
                            new_chemin.last++;
                        }
                        enqueueint(&new_chemin, moves);

                        new_noeud->fils[i] = creer_noeud(new_value, nb_fils - 1, phase + 1,
                                                         supp_mouv(mouv, nb_fils, mouv[i]), nb_mouv, new_chemin,
                                                         new_loc, map, tree);
                    } else {
                        printf("C  ");
                    }
                } else {
                    printf("P  ");
                }
            }
            printf("\n   ");
        }
        else {

            ajoute_noeud(&tree->feuille, new_noeud);
        }
    }
    else {

        ajoute_noeud(&tree->feuille, new_noeud);
    }
    return new_noeud;
}


void remplir_tree(ARBRE *tree, int parmi, int nb_mouv, t_localisation loc, t_map map)
{

    int *mouv = (int *)malloc(parmi*sizeof(int));
    for (int i = 0; i < parmi; i++){
        mouv[i] = random_int();
    }

    int val = map.costs[loc.pos.y][loc.pos.x];
    t_queue_int chemin = createQueueint(nb_mouv);

    int taille = 1;
    for (int i = parmi+1; i > parmi-nb_mouv; i--){
        taille = taille*i;
    }
    tree->feuille = createList(taille);

    tree->racine = creer_noeud(val, parmi, 0, mouv, nb_mouv, chemin, loc, map, tree);

}





NOEUD *trouver_min(ARBRE *tree)
{
    t_list_noeud liste = tree->feuille;
    NOEUD *min = liste.values[0];
    for (int i = 1; i < liste.nbElts; i++){
        if (liste.values[i]->val < min->val){
            min = liste.values[i];
        }
    }
    return min;
}






void deplacement(t_localisation *loc, int nb_mouv, t_queue_int chemin)
{

    t_move moves;
    for (int i = 0; i < nb_mouv; i++){
        moves = dequeueint(&chemin);
        updateLocalisation(loc, moves);
    }
    return;
}





void guidage_MARC(t_localisation loc, t_map map)
{
    int arrive = 0;
    int parmi = 5;
    int nb_mouv = 3;
    clock_t debut, fin, debut_guidage, fin_guidage;

    debut_guidage = clock();
    srand(time(NULL));
    while (!arrive) {

        ARBRE *t = createtree();
        debut = clock();
        remplir_tree(t, parmi, nb_mouv, loc, map);
        fin = clock();
        printf("\n");
        printf("Temps d'execution pour remplir l'arbe : %f secondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);

        debut = clock();
        NOEUD *min = trouver_min(t);
        fin = clock();
        printf("Noeud avec le plus petit cout : (%d, %d) et il vaut : %d\n", min->loc.pos.x, min->loc.pos.y, min->val);
        printf("Temps de recherche : %f secondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);

        deplacement(&loc, min->chemin.last, min->chemin);
        printf("loc apres deplacement : (%d, %d)\n", loc.pos.x, loc.pos.y);
        if (min->val == 0) {
            arrive = 1;
            printf("Arrivee a la base !\n");
        }
    }
    fin_guidage = clock();
    printf("Temps d'execution pour le guidage : %f secondes\n", (double)(fin_guidage - debut_guidage) / CLOCKS_PER_SEC);
}
