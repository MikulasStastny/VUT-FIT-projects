// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include "htab_structs.h"

/**
 * @brief Pro všechny prvky zadané tabulky se provede zadaná funkce.
 * 
 * @param t tabulka, pro jejíž prvky se vykoná funkce
 * @param f funkce, která se vykoná na všechny prvky tabulky
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){

    // Pomocná proměnná.
    htab_item_t *item;

    // Cyklus přes všechny prvky pole arr_ptr.
    for(size_t i = 0; i < t->arr_size; i++){
        item = t->arr_ptr[i];

        // Cyklus přes všechny prvky linked listu.
        while(item != NULL){
            (*f)(&item->pair);
            item = item->next;
        }
    }
}