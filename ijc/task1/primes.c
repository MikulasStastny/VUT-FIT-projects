/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad A)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "eratosthenes.h"

int main(){
	clock_t start;

	start = clock();

	bitset_alloc(pole, 300000000);

	Eratosthenes(pole);

	unsigned long idx = bitset_size(pole) - 1;

	for(int counter = 0; counter < 10 && idx > 0; idx--){
		if(!(bitset_getbit(pole, idx)))
			counter++;
	}

	for(unsigned long i = idx; i < bitset_size(pole); i++){
		if(!(bitset_getbit(pole, i)))
			printf("%lu\n", i);
	}

	fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

	bitset_free(pole);
}
