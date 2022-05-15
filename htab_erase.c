//htab_erase.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 18.04.2022

//b=htab_erase(t,key)       zrušení záznamu se zadaným klíčem (úspěch:true)
//                          Když průměrná délka seznamů klesne pod vámi
//                          definovaný limit AVG_LEN_MIN provede operaci
//htab_resize na poloviční velikost.

#include <string.h>
#include "htab.h"
#include <stdlib.h>
#include <stdio.h>

// po zkouseni jsem zjistil, ze idealni MIN je :
#define MIN 0.25

bool htab_erase(htab_t *t, htab_key_t key)
{
    bool b_erase= false;
    // pozice arr ve vetvi
    size_t position = htab_hash_function(key) % htab_bucket_count(t);
    htab_list_t *nod = t->htab_ptr[position];

    // pokud dana vetev je NULL tak return false
    if(nod == NULL)
    {
        return b_erase;
    }

    // pokud se jedna o prvni prvek ve vetvi
    if((strcmp(nod->pair->key,key)) == 0)
    {
        htab_list_t *afterNod = nod->next  ;

        free(nod);
        t->htab_ptr[position] = afterNod;
        (t->actual_size)--;                 // zmenseni size prvku hashovaci tabulky
        b_erase= true;
    }else
    {
        // nejedna se o prvni prvek ve vetvi => projdu for cyklem na dany prvek
        for(;nod->next != NULL && strcmp(nod->next->pair->key,key) ;nod = nod->next);

        if(strcmp(nod->next->pair->key,key) == 0)
        {
        htab_list_t *afterNod = nod->next->next  ;

        free(nod->next);
        nod->next = afterNod;               // nastaveni ukazatele na dalsi prvek
        (t->actual_size)--;                 // zmenseni size prvku hashovaci tabulky
        b_erase= true;                      // nastaveni navratove hodnoty na true
        }
    }
    return b_erase;
}
