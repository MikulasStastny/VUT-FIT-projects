/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad B)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "error.h"

void ppm_free(struct ppm *p){
    free(p);
}

struct ppm *ppm_read(const char *filename){
    FILE *file;

    file = fopen(filename, "r");

    if(file == NULL){
        warning_msg("Nepodarilo se otevrit soubor %s!", filename);
        return NULL;
    }

    char file_type[3];
    unsigned xsize, ysize, color;

    if(fscanf(file, "%2s\n%u %u\n%u\n", file_type, &xsize, &ysize, &color) != 4){
        error_exit("Chyba cteni souboru!");
    }

    if(strcmp(file_type, "P6") != 0 || color > 255 || xsize > MAX_SIZE || ysize > MAX_SIZE){
        fclose(file);
        warning_msg("Spatny format souboru %s. Typ by mel byt P6, rozsah barvy 0-255 a maximalni velikost 8000x8000!", filename);
        return NULL;
    }

    struct ppm *picture = (struct ppm*) malloc(sizeof(unsigned)*2 + sizeof(unsigned char)*3*xsize*ysize);

    if(picture == NULL){
        fclose(file);
        warning_msg("Chyba alokace pameti!");
        return NULL;
    }

    picture->xsize = xsize;
    picture->ysize = ysize;

    int character;

    for(unsigned i = 0;(character = fgetc(file)) != EOF && i < 3*xsize*ysize; i++){
        picture->data[i] = character;
    }

    fclose(file);

    return picture;
}
