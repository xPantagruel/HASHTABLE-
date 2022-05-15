//zdroj: (http://www.cse.yorku.ca/~oz/hash.html - varianta sdbm):
#include "htab.h"
#include <stdint.h>

size_t htab_hash_function(const char *str)
{
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}