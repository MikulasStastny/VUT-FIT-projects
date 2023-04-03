/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad B)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <stdio.h>

#include "error.h"
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"

int main (int argc, char **argv){
	if(argc != 2)
		error_exit("Spatny pocet argumentu! Mel by byt jeden! Pocet argumentu: %d", argc-1);

	struct ppm *picture;

	picture = ppm_read(argv[1]);

	if(picture == NULL){
		return -1;
	}

	const unsigned data_size = 3*picture->xsize*picture->ysize;

	bitset_alloc(pole, data_size);

	Eratosthenes(pole);

	unsigned shift = 0, idx = 0;
	unsigned char lsb;
	char message[200] = {0};

	for(unsigned long i = 28; i < bitset_size(pole) && idx < 200; i++){
		if(!(bitset_getbit(pole, i))){
			lsb = picture->data[i] & (unsigned char) 1;
			message[idx] = message[idx] | (lsb << shift);
			shift++;
		}
		if(shift == 8){
			if(message[idx] == '\0')
				break;
			shift = 0;
			idx++;
		}
	}
	
	if(message[idx] != '\0'){
		error_exit("Zprava neni ukoncena nulovym znakem!\n");
	}

	printf("%s\n", message);

	ppm_free(picture);
	bitset_free(pole);
}
