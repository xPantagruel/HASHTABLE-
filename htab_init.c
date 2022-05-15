//htab_init.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 11.04.2022

//t=htab_init(num)          konstruktor: vytvoření a inicializace tabulky
//num = počet prvků pole (.arr_size)

#include "htab.h"
#include <stdlib.h>

htab_t * htab_init(size_t num_size)
{
    htab_t *hash = malloc(sizeof(htab_t) + num_size * sizeof(htab_list_t) );

    // pri chybe alokovani return NULL
    if (hash == NULL)
    {
        return hash;
    }else if(hash != NULL)
    {
        hash->actual_size = 0;      // nastaveni poctu prvku na 0
        hash->n_size_arr= num_size; // nastaveni velikosti array na zadanou num_size

        // cyklus pro posun po vetvich
        for (size_t i = 0; i < num_size; i++)
        {
            hash->htab_ptr[i]= NULL;    // nastaveni vetve na NULL
        }
    }
    return  hash;

}
