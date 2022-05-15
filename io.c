//io.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 18.04.2022

//Napište funkci
//
//int read_word(char *s, int max, FILE *f);
//
//která čte jedno slovo ze souboru f do zadaného pole znaků
//        a vrátí délku slova (z delších slov načte prvních max-1 znaků,
//a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
//Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
//Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
//
//Omezení: řešení v C bude tisknout jinak uspořádaný výstup
//a je povoleno použít implementační limit na maximální
//délku slova (např. 127 znaků), delší slova se ZKRÁTÍ a program
//při prvním delším slovu vytiskne varování na stderr (max 1 varování).

#include <ctype.h>
#include "io.h"
int read_word(char *s, int max, FILE *f)
{
    int max_ = max-1;
    int l= 0;
    int character=0;
    int position=0;

    while ((character= fgetc(f))!=EOF)
    {
        if (!(isspace(character)))
        {
            l++;
            if(position < max)
            {
                s[position]=character;
                position++;
            }
        }else
        {
            break;
        }
    }
    // kontrola podminky zda se nejedna o konec souboru
    if(character == EOF)
    {
        return EOF;
    }
    // zkonceni array koncovou nulou
    s[position] = '\0';

    // return delky slova
    return l;
}