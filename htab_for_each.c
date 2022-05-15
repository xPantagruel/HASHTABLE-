//htab_for_each.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 16.04.2022

//htab_for_each(t,funkce)   projde všechny záznamy, na každý zavolá funkci

#include "htab.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    // posun po vetvich
    for (size_t i = 0; i < t->n_size_arr ; i++)
    {
        htab_list_t * nod = t->htab_ptr[i]; //deklarace ukazatele na posun

        // posun po prvcich ve vetvi
        while(nod != NULL)
        {
            (*f)(nod->pair);    // zavolani funkce na pair
            nod = nod->next;    // posun po vetvich
        }
    }
}