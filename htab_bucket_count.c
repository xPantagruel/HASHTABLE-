//htab_bucket_count.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 15.04.2022

#include "htab.h"

size_t htab_bucket_count(const htab_t *t)
{
    return t->n_size_arr;
}

