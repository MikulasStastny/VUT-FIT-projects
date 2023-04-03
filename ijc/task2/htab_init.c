// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdlib.h>
#include "htab_structs.h"

/**
 * @brief Alokuje paměť pro tabulku a inicializuje ji.
 * 
 * @param n velikost pole linked listů
 * @return htab_t* - ukazatel na novou tabulku
 */
htab_t *htab_init(size_t n){

    if(n == 0){
        fprintf(stderr, "htab_init: velikost tabulky nesmí být nula!\n");
        return NULL;
    }

    // Alokace paměti pro tabulku.
    htab_t *hash_table = (htab_t *) malloc(sizeof(htab_t));

    if(hash_table == NULL){
        fprintf(stderr, "htab_init: alokace paměti pro hashovací tabulku selhala!\n");
        return NULL;
    }

    // Inicializace hodnot tabulky.
    hash_table->size = 0;
    hash_table->arr_size = n;

    // Alokace paměti pro pole arr_ptr o velikosti n.
    hash_table->arr_ptr = (htab_item_t **) malloc(sizeof(htab_item_t)*n);

    // Inicializace všech prvků arr_ptr na prázdné seznamy.
    for(size_t i = 0; i < n; i++){
        hash_table->arr_ptr[i] = NULL;
    }

    return hash_table;
}
