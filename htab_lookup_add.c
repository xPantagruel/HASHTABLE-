//htab_lookup_add.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 17.04.2022

// htab_pair_t htab_lookup_add(htab_t *t, htab_key_t key);
// V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
// - pokud jej nalezne, vrátí ukazatel na záznam
// - pokud nenalezne, automaticky přidá záznam a vrátí ukazatel
//         Když průměrná délka seznamů přesáhne vámi definovaný limit
//         AVG_LEN_MAX provede operaci htab_resize na dvojnásobnou velikost.
// Poznámka: Dobře promyslete chování této funkce k parametru key.
// Poznámka: podobně se chová C++ operator[] pro std::unordered_map

#include "htab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// po zkouseni jsem zjistil, ze idealni MAX je :
#define MAX 0.5


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    // zjisteni pozice v hash table
    size_t position = htab_hash_function(key) % htab_bucket_count(t);
    // vetev kterou hledam
    htab_list_t *nod = t->htab_ptr[position];
    // navratova hodnota
    htab_pair_t *duo = NULL;

    // vetev je NULL
    //      - pridam novy prvek
    //      - zkontroluju resize
    if(nod == NULL)
    {
        htab_pair_t  *pair = malloc(sizeof(htab_pair_t));       // alokace pro novy pair
        htab_list_t *newItem = malloc(sizeof(htab_list_t));     // alokace pro novy list

        char *key_copy = calloc(strlen(key)+1,sizeof(char));    // alokace a vynulovani pro dane slovo
        strcpy(key_copy,key);   // zkopirovani retezce key do key_copy

        pair->key = key_copy;   // nastaveni noveho klice
        pair->value=0;          // nastaveni hodnoty

        newItem->pair=pair;     // nasteveni pointeru na vytvorenou dvojici
        newItem->next=NULL;     // nastaveni nasledujiciho prvku na NULL
        (t->actual_size)++;     // zvyseni poctu prvku

        t->htab_ptr[position]=newItem;

        duo = t->htab_ptr[position]->pair;

        return duo;
    }

    // vetev neni NULL a existuje prvek => vracim pointer
    while(nod != NULL)
    {
        // pokud key uz exituje
        if((strcmp(nod->pair->key,key)) == 0)
        {
            (t->actual_size)++;

            duo = nod->pair;

            return duo;

        }
        nod = nod->next;
    }


    // vetev neni NULL a neexistuje prvek
    //      - projedu seznam az nakonec kde vytvorim novy prvek na kterej bude ukazovat predesly
    //      - zkontroluju resize

    htab_list_t *nod_end = t->htab_ptr[position];

    // cyklus pro posun na konec vetve
    for(;nod_end->next != NULL ;nod_end = nod_end->next);

    if (nod_end->next == NULL )
    {
        // stejna inicializace jako prvniho prvku
        htab_pair_t  *pair = malloc(sizeof(htab_pair_t));
        htab_list_t *newItem = malloc(sizeof(htab_list_t));

        char *key_copy = calloc(strlen(key)+1,sizeof(char));
        strcpy(key_copy,key);

        pair->key = key_copy;
        pair->value=0;

        newItem->pair=pair;
        newItem->next=NULL;
        (t->actual_size)++;

        nod_end->next=newItem;

        duo = nod_end->next->pair;

        return duo;
    }
    return duo; // navratova hodnota NULL pri nepovedenem pridani
}