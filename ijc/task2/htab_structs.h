// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#ifndef HTAB_STRUCTS
#define HTAB_STRUCTS

#include "htab.h"

typedef struct htab_item htab_item_t;

struct htab{
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

struct htab_item {
    htab_pair_t pair;
    htab_item_t *next;
};

#endif
