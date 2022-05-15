//htab_size.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 15.04.2022

#include "htab.h"

size_t htab_size(const htab_t *t)
{
    return t->actual_size;
}

