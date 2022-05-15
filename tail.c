//tail.c
//Řešení IJC-DU2
//Autor: Matej Macek, FIT
//Datum: 011.04.2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 4095
// funkce spocita pocet radku v souboru
// a dostane se na celkovy pocet radku bez n
// a zacne vypisovat radky dokud nevypise n radku
void print_tail (FILE *f_file, long int num_lines_print)
{
    FILE *fileptr = f_file;

    // counting number of lines
    long int line_counter = 0;
    char chr01= fgetc(fileptr) ;

    while(chr01 != EOF)
    {
        if(chr01 == '\n')
        {
            line_counter = line_counter +1;
        }
        chr01= fgetc(fileptr);
    }

    rewind(fileptr);

    char chr02= fgetc(fileptr) ;
    int i =0,j=0;
    // line,collums
    char file[line_counter][LINE_SIZE];


    // zapsani dat do kralikarny
    while(chr02 != EOF)
    {
        file[i][j]=chr02;
        chr02=fgetc(fileptr);

        if(chr02 == '\n')
        {
            file[i][j+1]=chr02;
            chr02=fgetc(fileptr);
            i=i+1;
            j=0;
            continue;
        }
        j=j+1;

    }


    //  vypsani radku od konce o poctu n
    for (long int k = line_counter -num_lines_print -1  ; k < line_counter; k++)
    {
        for ( unsigned int l = 0;l < strlen(file[k]); l++) {
            putc(file[k][l],stdout);
        }
    }
}
int main(int argc, char *argv[])
{
    long num_lines= 9;
    FILE * file_for_read = NULL;

    // kontrola spravneho poctu argumentu
    if(argc > 4)
    {
        fprintf(stderr, "%s", "Spatne zadane argumenty\n");
        return 1;
    }

    if(argc == 2 || argc == 4)
    {
        file_for_read= fopen(argv[argc-1], "r" );

        // pri chybnem nacteni souboru se vypise na STDERR chyba
        if(file_for_read == NULL)
        {
            fprintf(stderr, "Nelze nacist soubor \n");
            return 1;
        }
    }

    // pri nezadanem souboru cteni z prikazove radky
    if(file_for_read == NULL)
    {
        file_for_read=stdin;
    }

    if(argc == 2 )
    {

    } else if(argc == 4)
    {
        if(strcmp(argv[1], "-n") != 0)//kontrola argumentu "-n"
        {
            fprintf(stderr, "Nezadan argument -n\n");
            return 1;

        }else
        {
            //-1 abych dostal pocet 2d poli kde pocet se inicializuje uz od 0 file[0][0]
            num_lines = strtol(argv[2], NULL, 0)-1;
            if (num_lines < 0)
            {
                fprintf(stderr, "Zaporne cislo za -n nelze\n");
                return 1;
            }
        }
    }
    // zavolani funkce pro nahrani dat a print
    print_tail(file_for_read, num_lines);
    fclose(file_for_read);
}