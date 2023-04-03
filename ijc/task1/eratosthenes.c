/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad A)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <stdio.h>
#include <math.h>

#include "eratosthenes.h"
#include "bitset.h"

void Eratosthenes(bitset_t pole){

	float sqrt_size = sqrt(pole[0]);

	bitset_setbit(pole, 0, 1);
	bitset_setbit(pole, 1, 1);

	for(unsigned long i = 2; i < sqrt_size; i++){
		if(!(bitset_getbit(pole, i))){
			for(unsigned long j = 2*i; j < pole[0]; j += i){
				bitset_setbit(pole, j, 1);
			}
		}
	}
}