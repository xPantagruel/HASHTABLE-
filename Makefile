#MAKEFILE
#Řešení IJC-DU2
#Autor: Matej Macek, FIT
#Datum: 09.04.2022

GCC = gcc -std=c11 -pedantic -Wall -Wextra

all: tail wordcount wordcount-dynamic

tail: tail.o
	$(GCC) tail.c -o tail

wordcount: wordcount.o io.o libhtab.a
	$(GCC)  -fPIC -static -o wordcount wordcount.o io.o -L. -lhtab

wordcount-dynamic: wordcount.o io.o libhtab.so
		$(GCC) -fPIC -o wordcount-dynamic wordcount.o io.o -L. -lhtab

libhtab.a:htab_hash_function.o htab_for_each.o htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_free.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
	ar crs libhtab.a $^

libhtab.so:htab_hash_function.o htab_for_each.o htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_free.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
	$(GCC) -shared -o libhtab.so $^

zip:
	zip xmacek27.zip *.c *.h Makefile

clean:
	rm -f *.o tail wordcount wordcount-dynamic libhtab.a libhtab.so