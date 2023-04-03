// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include "htab_structs.h"

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}
