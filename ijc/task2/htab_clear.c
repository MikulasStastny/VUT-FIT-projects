// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdlib.h>

#include "htab_structs.h"

/**
 * @brief Uvolní paměť všech prvků tabulky a inicializuje seznamy na prázdné.
 * 
 * @param t tabulka, která bude vyprázdněna
 */
void htab_clear(htab_t * t){
    // Pomocné proměnné.
    htab_item_t *tmp, *tmp1;

    // Projde každý linked list z arr_ptr a uvolní pamět všech jejich prvků.
    // Nakonec nastaví liked listy na prázdné seznamy.
    for(size_t i = 0; i < t->arr_size; i++){
        tmp = t->arr_ptr[i];

        while(tmp != NULL){
            tmp1 = tmp->next;
            free((char *)tmp->pair.key);
            free(tmp);
            tmp = tmp1;
        }
        t->arr_ptr[i] = NULL;
    }

    // Aktualizace hodnoty počtu prvků tabulky.
    t->size = 0;
}
