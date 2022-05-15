//wordcount.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 18.04.2022

#include "htab.h"
#include <stdio.h>
#include "io.h"

#define MAX 128
#define SIZE_OF_TAB 15070 // jedna se o prvocisla

/* zduvodneni velikosti SIZE_OF_TAB:
 *      -pouzivam prvocislo z duvodu snizeni sance na shlukovani u nekterych funkci
 *      -nevime predem kolik bude potreba mista tak proto volim vetsi velikost, abych pak nazatezoval procesor
 *      -jde nam o to aby vyhledavan odpovidalo 0(1)
 *      -v nasem pripade vetsi pocatecni pole znamena rychlejsi pristup k datum
*/

#ifdef HASHTEST
//  Hash function : lose lose
//  odkaz na zdroj http://www.cse.yorku.ca/~oz/hash.html
size_t htab_hash_function(const char *str)
{
	unsigned int hash = 0;
	int c;

	while (c = *str++)
	    hash += c;

	return hash;
}

#endif

void pair_print(htab_pair_t *nod)
{
    printf("%s\t%d\n",nod->key,nod->value);
}

int main(int argc, char *argv[])
{
    htab_t *hash_table = htab_init(SIZE_OF_TAB);    // vytvoreni prazdneho hash table
    int l = 0,ex_w=0;   // l = delka daneho slova ; ex_w= pomocna promenna pro kontrolu zda jsme presahli delku slova pro ulozeni
    char in[MAX]={0};   // vynulovani a deklarace retezce
    FILE *f;

    // nastaveni zdda jde o cteni ze stdin nebo souboru
    if(argc == 1)
    {
        f=stdin;
    }
    else
    {
        f=fopen(argv[1], "r" );
    }

    // cyklus, ktery projde slova
    while((l = read_word(in,MAX,f)) != EOF) // inicializace l, in
    {
        // pokud slovo presahne delku definovanou
        if (l > (MAX -1) && ex_w ==0 )
        {
            ex_w=1;
            fprintf(stderr, "Slovo bylo delsi nez limit takze zbytek slova se odsekl");
        }

        // pokud delka je 0 preskoci se nasleduji cast cyklu
        if(l)
        {
            // pridani slova do hash table
            htab_pair_t *p = htab_lookup_add(hash_table,in);
            // zvednuti poctu slov
            (p->value)++;
        }else
        {
            continue;
        }
    }
    // zavolani funkce pair_print na hash_table
    htab_for_each(hash_table,pair_print);
    htab_free(hash_table);

    return 0;
}
