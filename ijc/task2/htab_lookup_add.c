// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdlib.h>

#include "htab_structs.h"

/**
 * @brief Pokusí se přidat nový prvek se zadaným klíčem do tabulky a vrátí na něj ukazatel.
 *        Jesliže prvek v tabulce už je, zvýší hodnotu jeho počtu výskytů a vrátí na něj ukazatel.
 * 
 * @param t tabulka, do které se přidá prvek
 * @param key string, který bude sloužit jako klíč nového prvku
 * @return htab_pair_t* - vrátí ukazatel na pair nově vytvořeného nebo
 *         nalezeného prvku, nebo NULL v případě, že alokace paměti selhala
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){

    // Najde, jestli v tabulce už není prvek s key.
    htab_pair_t *wanted_pair = htab_find(t, key);

    // Pokud už v tabulce prvek je, zvýsí jeho hodnotu výskytů a vrátí ukazatel na něj.
    if(wanted_pair != NULL){
        wanted_pair->value++;
        return wanted_pair;
    }

    // Do index vloží hodnotu indexu pole arr_ptr pro prvek s key podle htab_hash_function.
    size_t index = (htab_hash_function(key) % t->arr_size);

    htab_item_t *item = t->arr_ptr[index];

    // Jestliže arr_ptr[index] je prázdný seznam, provede následující kód.
    if(item == NULL){
        // Alokace paměti pro jeden prvek.
        t->arr_ptr[index] = malloc(sizeof(htab_item_t));
        if(t->arr_ptr[index] == NULL)
            return NULL;

        //Alokace paměti pro string key.
        t->arr_ptr[index]->pair.key = malloc(sizeof(char)*(strlen(key)+1));
        if(t->arr_ptr[index]->pair.key == NULL)
            return NULL;

        // Inicializace hodnot nově vloženého prvku.
        strcpy((char *)t->arr_ptr[index]->pair.key, key);
        t->arr_ptr[index]->pair.value = 1;
        t->arr_ptr[index]->next = NULL;

        // Pomocná proměnná, která uloží správný pair pro return funkce, když by se provedl resize.
        // (Při přeskupení tabulky by totiž t->arr_ptr[index]->pair nemusel být stejný jako předtím!)
        htab_pair_t *tmp_pair = &t->arr_ptr[index]->pair;

        // Zvýšení hodnoty počtu prvků v tabulce.
        t->size++;

        // Provede resize podle zadání.
        if(t->size/t->arr_size > AVG_LEN_MAX){
            htab_resize(t, t->arr_size*2);
        }

        return tmp_pair;
    }
    
    // Najde poslední prvek v neprázdném seznamu. Do jeho následujícího prvku vloží nový
    // prvek s key. Jinak struktura stejná jako v předchozím if bloku.
    while(item->next != NULL){
        item = item->next;
    }

    item->next = malloc(sizeof(htab_item_t));
    if(item->next == NULL){
        return NULL;
    }
        

    item->next->pair.key = malloc(sizeof(char)*(strlen(key)+1));
    if(item->next->pair.key == NULL){
        return NULL;
    }

    strcpy((char *)item->next->pair.key, key);
    item->next->pair.value = 1;
    item->next->next = NULL;

    // Pomocná proměnná, která uloží správný pair pro return funkce, když by se provedl resize.
    // (Při přeskupení tabulky by totiž item->next->pair nemusel být stejný jako předtím!)
    htab_pair_t *tmp_pair = &item->next->pair;

    t->size++;

    if(t->size/t->arr_size > AVG_LEN_MAX){
        htab_resize(t, t->arr_size*2);
    }

    return tmp_pair;
}
