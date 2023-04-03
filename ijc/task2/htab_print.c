// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>

#include "htab_structs.h"

/**
 * @brief Tiskne aktuální stav tabulky.
 * 
 * @param t tabulka k vytisknutí
 */
void htab_print(htab_t *t){
    htab_item_t *item;

    printf("size: %ld\n", t->size);

    for(size_t i = 0; i < t->arr_size; i++){
        printf("index %ld: ", i);
        item = t->arr_ptr[i];
        while(item != NULL){
            printf("(%s, %d)", item->pair.key, item->pair.value);
            item = item->next;
            if(item != NULL){
                printf("-->");
            }
        }
        printf("\n");
    }
    printf("\n");
}