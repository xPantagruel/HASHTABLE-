//htab_find.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 15.04.2022

//V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
//- pokud jej nalezne, vrátí ukazatel na záznam
//- pokud nenalezne, vrátí NULL

#include "htab.h"
#include <string.h>

// t....value = asociovaná data = počet výskytů
// key..ukazatel na dynamicky alokovaný řetězec
htab_pair_t *htab_find(htab_t *t,htab_key_t key)
{
    // pozice indexu hash funkce
    size_t position = htab_hash_function(key) % t->n_size_arr;

    // cyklus prochazejici vetve
    for (htab_list_t *nod = t->htab_ptr[position]; nod != NULL ; )
    {
        // porovnani zda se nejedena o key jinak se prejde na return
        if ((strcmp(key,nod->pair->key)) != 0)
        {
            nod = nod->next;
            continue;
        }

        return (htab_pair_t *) nod; // pointer na value a key, kde key odpovida zadanemu key
    }
    return NULL;    // navratova hodnota pri chybe
}