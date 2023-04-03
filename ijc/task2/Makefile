# autor: Mikuláš Šťastný, FIT
# uloha: IJC DU2, příklad A), B)
# přeloženo: gcc 11.2
# datum: 20. 4. 2022

CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra

CPPC=g++
CPPFLAGS=-O2 -std=c++17 -pedantic -Wall

OBJ=htab_init.o htab_free.o htab_size.o htab_bucket_count.o \
htab_hash_function.o htab_find.o htab_lookup_add.o htab_erase.o htab_clear.o \
htab_resize.o htab_print.o htab_for_each.o io.o

LIBS=htab_structs.h htab.h

.PHONY: all clean zip

all: tail template wordcount wordcount-dynamic

tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

template: template.cc
	$(CPPC) $(CPPFLAGS) -o $@ $^

wordcount: wordcount.o libhtab.a
	$(CC) $(CFLAGS) -o $@ -static $^

wordcount-dynamic: wordcount.o libhtab.so
	$(CC) -o $@ $^

libhtab.a: $(OBJ)
	ar crs $@ $^

libhtab.so: $(OBJ)
	$(CC) -shared -o $@ $^



wordcount.o: wordcount.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_init.o: htab_init.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_free.o: htab_free.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_size.o: htab_size.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_bucket_count.o: htab_bucket_count.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_hash_function.o: htab_hash_function.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_find.o: htab_find.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_lookup_add.o: htab_lookup_add.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_erase.o: htab_erase.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_clear.o: htab_clear.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_resize.o: htab_resize.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_for_each.o: htab_for_each.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

htab_print.o: htab_print.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $^

io.o: io.c io.h
	$(CC) $(CFLAGS) -fPIC -c $^



clean:
	rm -f *.o *.gch *.so *.a tail wordcount wordcount-dynamic template

zip:
	zip xstast38.zip *.c *.cc *.h Makefile
