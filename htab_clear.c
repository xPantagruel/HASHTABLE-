//htab_clear.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 16.04.2022

//htab_clear(t)             zrušení všech položek, tabulka zůstane prázdná

#include "htab.h"
#include <stdlib.h>

void htab_clear(htab_t *t)
{
    // prochazeni vetvi
    for (size_t i = 0; i < htab_bucket_count(t) ; i++)
    {
        htab_list_t * nod = t->htab_ptr[i];

        while(nod != NULL)
        {
            // vytvoreni promenne pro odstraneni
            htab_list_t * del_nod = nod;
            nod = nod->next;
            free(del_nod);
        }
    }
}

