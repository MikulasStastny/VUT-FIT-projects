// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include "htab_structs.h"

/**
 * @brief Pokusí se najít prvek s key hodnotou v tabulce.
 * 
 * @param t tabulka, ve které se bude hledat
 * @param key klíč, podle kterého se bude hledat
 * @return htab_pair_t* - ukazatel na nalezený prvek, nebo NULL v případě,
 *         že prvek nebyl nalezen.
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key){

    // Určí index pole arr_ptr, ve kterém se bude hledat.
    size_t index = (htab_hash_function(key) % t->arr_size);

    // Pomocná proměnná.
    htab_item_t *item = t->arr_ptr[index];

    while(item != NULL){
        // Provede se, když byl prvek se zadaným key nalezen, funkce na něj vrátí ukazatel.
        if(strcmp(item->pair.key, key) == 0){
            return &item->pair;
        }
        item = item->next;
    }
    
    // Vrátí NULL v případě, že prvek nebyl nalezen.
    return NULL;
}
