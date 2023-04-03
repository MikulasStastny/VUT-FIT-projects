// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdlib.h>

#include "htab_structs.h"

/**
 * @brief Změní velikost tabulky a přeskupí prvky původní tabulky, aby
 *        byli uloženy na správných indexech daných funkcí htab_hash_function.
 * 
 * @param t upravovaná tabulka
 * @param newn nová velikost tabulky
 */
void htab_resize(htab_t *t, size_t newn){

    if(newn == 0){
        fprintf(stderr, "htab_resize: velikost tabulky nesmí být nula!\n");
        return;
    }

    // Pole prvků linked listů, do kterého si uložíme všechny prvky z tabulky.
    // Lze nahradit statickým polem (např.: htab_item_t *items[t->size];), ale při zadání
    // velkého souboru by nemusel stačit stack frame.
    htab_item_t **items = (htab_item_t **) malloc(sizeof(htab_item_t)*t->size);
    if(items == NULL){
        fprintf(stderr, "htab_resize: alokace paměti selhala!\n");
        return;
    }

    // Pomocná proměnná
    htab_item_t *item;
    // V první části funkce určuje index do pole items[], v druhé části určuje index z htab_hash_function % newn
    size_t index = 0;

    // Uložení prvků z tabulku do items[]
    for(size_t i = 0; i < t->arr_size; i++){
        item = t->arr_ptr[i];

        while(item != NULL){
            items[index] = item;
            index++;
            item = item->next;
        }
    }

    // Alokace paměti pro nové n.
    t->arr_ptr = (htab_item_t **) realloc(t->arr_ptr, sizeof(htab_item_t)*newn);
    if(t->arr_ptr == NULL){
        fprintf(stderr, "htab_resize: chyba alokace paměti, resize se neprovede!\n");
        return;
    }
    
    t->arr_size = newn;

    // Inicializace prvků pole arr_ptr (Ztratíme sice ukazatele na jednotlivé prvky linked listů,
    // ale nedojde k memory leaku, protože tyto ukazatele jsme si uložili do items[]).
    for(size_t i = 0; i< t->arr_size; i++){
        t->arr_ptr[i] = NULL;
    }

    // Vložení prvků z items[] do tabulky s novou velikostí.
    for(size_t i = 0; i < t->size; i++){
        items[i]->next = NULL;
        index = (htab_hash_function(items[i]->pair.key) % t->arr_size);
        item = t->arr_ptr[index];
        if(item == NULL){
            t->arr_ptr[index] = items[i];
        }
        else{
            while(item->next != NULL){
                item = item->next;
            }
            item->next = items[i];
        }
    }

    free(items);

}