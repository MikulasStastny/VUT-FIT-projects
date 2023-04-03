// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#include "htab_structs.h"


/**
 * @brief Jestliže najde prvek v tabulce, odstraní ho.
 * 
 * @param t tabulka, ve které se bude hledat
 * @param key string, podle kterého se bude hledat prvek v tabulce
 * @return true - prvek se úspěšně vymazal,
 *         false - prvek nebyl v tabulce nalezen
 */
bool htab_erase(htab_t * t, htab_key_t key){
    bool success = false;

    // Určí se, na jakém indexu pole arr_ptr se bude hledat.
    size_t index = (htab_hash_function(key) % t->arr_size);

    // Pomocné proměnné.
    htab_item_t *item = t->arr_ptr[index], *bef_item = NULL;

    while(item != NULL){
        // Provede se, když se nalezne prvek se stejnou key hodnotou.
        // Uvolní se paměť tohoto prvku a prvek se odstraní.
        if(strcmp(item->pair.key, key) == 0){
            if(bef_item == NULL){
                t->arr_ptr[index] = t->arr_ptr[index]->next;
            }
            else{
                bef_item->next = item->next;
            }

            free((char *)item->pair.key);
            free(item);
            
            t->size--;

            // Provede resize podle zadání
            if(t->size/t->arr_size < AVG_LEN_MIN){
                htab_resize(t, t->arr_size/2);
            }

            // Zadaný prvek se úspěšně vymazal, může se vyskočit z cyklu.
            success = true;
            break;
        }
        bef_item = item;
        item = item->next;
    }

    return success;
}
