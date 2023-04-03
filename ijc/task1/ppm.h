/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad B)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#ifndef PPM
#define PPM

#define MAX_SIZE 8000

struct ppm{
		unsigned xsize;
		unsigned ysize;
		unsigned char data[]; // RGB bajty, celkem 3*xsize*ysize
};

// nacte obsah PPM souboru do touto funkci dynamicky alokované struktury
struct ppm *ppm_read(const char *filename);

// uvolni pamet dynamicky alokovanou v ppm_read
void ppm_free(struct ppm *p);

#endif
