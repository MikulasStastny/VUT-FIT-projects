
# autor: Mikulas Stastny, FIT
# uloha: IJC DU1, příklad A), B)
# přeloženo: gcc 11.2
# datum: 20. 3. 2022

CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS= -O2
LDLIBS= -lm

.PHONY: all run clean

all: primes primes-i steg-decode

run: primes primes-i
	./primes && ./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -o primes primes.o eratosthenes.o error.o $(LDLIBS)

primes-i: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -DUSE_INLINE -o primes-i primes.o eratosthenes.o error.o $(LDLIBS)

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $(LDFLAGS) -o steg-decode steg-decode.o ppm.o error.o eratosthenes.o $(LDLIBS)

primes.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c primes.c

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c eratosthenes.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

steg-decode.o: steg-decode.c ppm.c error.c error.h eratosthenes.c ppm.h bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c steg-decode.c

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c

clean:
	rm -f *.o primes primes-i steg-decode
