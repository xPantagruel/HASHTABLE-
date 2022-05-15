//htab_resize.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 18.04.2022

#include "htab.h"
#include <stdio.h>

void htab_resize(htab_t *t, size_t newnum)
{
    size_t oldTableSize = t->n_size_arr;    // stary index array


    htab_pair_t *duo = NULL;                 // deklarace funkce pro ukazatel na dvojici
    htab_t *oldTable = t;                    // ukazatel na stary table
    htab_t *NewTable = htab_init(newnum); // deklarace a zavolani funkce init na vytvoreni nove Htab
    htab_list_t *tmp = NULL;

    // cyklus zapisujici stare prvky do noveho htab
    for (size_t i = 0; i < oldTableSize; i++)
    {
        tmp = t->htab_ptr[i];
        while(tmp != NULL)
        {
            // duo je ukazatel na dvojici aktualni
            duo= htab_lookup_add(NewTable,tmp->pair->key);
            duo->value = tmp->pair->value;
            tmp = tmp->next;    // posun po hash table
        }
    }
    *t=*NewTable; // nastaveni pointeru na novy hash table
    for (size_t i = 0; i < NewTable->n_size_arr; i++)
    {
        tmp = NewTable->htab_ptr[i];
        while(tmp != NULL)
        {
            // duo je ukazatel na dvojici aktualni
            duo= htab_lookup_add(t,tmp->pair->key);
            duo->value = tmp->pair->value;
            tmp = tmp->next;    // posun po hash table
        }
    }
}
