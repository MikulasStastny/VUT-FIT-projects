// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdbool.h>

#include "htab_structs.h"
#include "io.h"

#define MAX_WORD_LENGTH 127

void print_pair(htab_pair_t *pair){
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(){
    htab_t *table = htab_init(3);

    if(table == NULL)
        return -1;

    char word[MAX_WORD_LENGTH] = "\0";

    // slouží pro kontrolu správné alokace paměti ve funkci htab_lookup_add.
    htab_pair_t *check_null = NULL;

    // Proměnné sloužící k správnému tisku chyby, když se překročí stanovený limit délky slova.
    bool error_printed = false;
    int check_too_long_word = 0;

    // scanf("%127s", word)

    // Načte jednotlivá slova ze stdin a jako klíče je uloží do tabulky.
    while(read_word(word, MAX_WORD_LENGTH, stdin) != EOF){
        if(check_too_long_word == 1 && !error_printed){
            fprintf(stderr,"wordcount: některé slovo je delší než povolený limit!\n");
            error_printed = true;
        }

        check_null = htab_lookup_add(table, word);
        if(check_null == NULL){
            fprintf(stderr, "wordcount: chyba alokace paměti!\n");
            htab_free(table);
            return -1;
        }
    }

    // Pro každý prvek tabulky vytiskne jeho pair.
    htab_for_each(table, print_pair);

    // Uvolní veškerou alokovanou paměť pro tabulku.
    htab_free(table);
}
