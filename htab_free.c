//htab_free.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 16.04.2022

// htab_free(t)              destruktor: zrušení tabulky (volá htab_clear())

#include "htab.h"
#include <stdlib.h>

void htab_free(htab_t *t)
{
    htab_clear(t);  // zavolani funkce clear na hash table
    free(t);
}

