/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad A)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <assert.h>
#include <stdlib.h>
#include "error.h"

#ifndef BITSET
#define BITSET

// Typ indexu do bitového pole.
typedef unsigned long bitset_index_t;

// Typ bitoveho pole (pro predavani parametru do funkce odkazem).
typedef bitset_index_t* bitset_t;

#define LU_SIZE (sizeof(unsigned long)*__CHAR_BIT__)

// Definuje a nuluje bitove pole jmeno_pole.
#define bitset_create(jmeno_pole, size) \
	static_assert((size) > 0, "Velikost pole musi byt vetsi nez nula!"); \
	bitset_index_t jmeno_pole[(size/LU_SIZE) + ((size%LU_SIZE) != 0 ? 1 : 0) + 1] = {(unsigned long) size};

// Definuje a nuluje bitove pole jmeno_pole tak, aby bylo alokovano dynamicky.
#define bitset_alloc(jmeno_pole, size) \
	assert((size) > 0); \
	bitset_t jmeno_pole = calloc((size/LU_SIZE) + ((size%LU_SIZE) != 0 ? 1 : 0) + 1, sizeof(bitset_index_t)); \
	jmeno_pole[0] = (unsigned long) size; \
	if(jmeno_pole == NULL) \
		error_exit("bitset_alloc: Chyba alokace paměti")

#ifndef USE_INLINE

	// Uvolni pamet dynamicky alokovaneho pole.
	#define bitset_free(jmeno_pole) free(jmeno_pole)

	// Vrati deklarovanou velikost pole v bitech.
	#define bitset_size(jmeno_pole) jmeno_pole[0]

	// Nastavi zadany bit v poli na hodnotu zadanou vyrazem.
	#define bitset_setbit(jmeno_pole, index, vyraz) \
		if((unsigned long) index >= bitset_size(jmeno_pole)){ \
			error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t) index, bitset_size(jmeno_pole) - 1); \
		} \
		if((int)vyraz) \
			jmeno_pole[(index/LU_SIZE) + 1] |= (1UL << ((LU_SIZE - ((bitset_index_t)index%LU_SIZE)) - 1)); \
		else \
			jmeno_pole[(index/LU_SIZE) + 1] &= ~(1UL << ((LU_SIZE - ((bitset_index_t)index%LU_SIZE)) - 1))

	// Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1.
	#define bitset_getbit(jmeno_pole, index) \
		((unsigned long) index >= bitset_size(jmeno_pole)) ? \
		(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t) index, bitset_size(jmeno_pole) - 1), 0) : \
		(jmeno_pole[index/LU_SIZE + 1] & (1UL << (LU_SIZE - (index%LU_SIZE) - 1)))

#else

	// Uvolni pamet dynamicky alokovaneho pole.
	inline void bitset_free(bitset_t pole){
		free(pole);
	}

	// Vrati deklarovanou velikost pole v bitech.
	inline bitset_index_t bitset_size(bitset_t pole){
		return pole[0];
	}

	// Nastavi zadany bit v poli na hodnotu zadanou vyrazem.
	inline void bitset_setbit(bitset_t pole, bitset_index_t index, int vyraz){
		if(index >= bitset_size(a)){
			error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, bitset_size(a) - 1);
		}

		if(vyraz)
			pole[(index/LU_SIZE) + 1] |= (1UL << (LU_SIZE - (index%LU_SIZE) - 1));
		else
			pole[(index/LU_SIZE) + 1] &= ~(1UL << (LU_SIZE - (index%LU_SIZE) - 1));

	}

	// Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1.
	inline unsigned long bitset_getbit(bitset_t pole, bitset_index_t index){
		if(index >= bitset_size(a)){
			error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, bitset_size(a) - 1);
		}
	
		return (pole[index/LU_SIZE + 1] & (1UL << (LU_SIZE - (index%LU_SIZE) - 1)));
	}

#endif
#endif
