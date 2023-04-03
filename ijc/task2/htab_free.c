// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad B)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdlib.h>

#include "htab_structs.h"

void htab_free(htab_t * t){
    
    htab_clear(t);

    free(t->arr_ptr);

    free(t);
}
