// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdbool.h>

#include "io.h"

/**
 * @brief Funkce načte do zadaného pole znaků slovo ze zadaného souboru o maximální délce.
 * 
 * @param s pole znaků, do kterého se načte slovo
 * @param max maximální počet znaků
 * @param f soubor, ze kterého se čte
 * @return int 0 - průběh bez chyby, 1 - slovo je moc dlouhé, EOF - konec souboru
 */
int read_word(char *s, int max, FILE *f){

    // znak načtený ze vstupu
    char a;

    // počítadlo
    int i = 0;

    bool too_long_word = false;

    // Přeskočí bílé znaky na začátku.
    while((a = fgetc(f)) == '\n' || a == ' ' || a == '\t');
    
    // Uloží první znak do pole s a ikrementuje počítadlo.
    s[i] = a;
    i++;

    // Načítání nebílých znaků do pole znaků s
    while((a = fgetc(f)) != '\n' && a != '\n' && a != ' ' && a != '\t' && a != EOF && i < max-1){
        s[i] = a;
        i++;
    }

    // Jestliže délka slova překročila limit, přeskočí další znaky.
    if(i == max-1){
        too_long_word = true;
        while((a = fgetc(f)) != '\n' && a != ' ' && a != '\t' && a != EOF);
    }

    // Poslední znak slova nastaví na nulový znak.
    s[i] = '\0';

    // Narazilo se na konec souboru.
    if(a == EOF)
        return EOF;

    // Vrátí jedna, jestliže je slovo moc dlouhé.
    if(too_long_word)
        return 1;

    return 0;
}
