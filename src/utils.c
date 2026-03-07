#include "utils.h"

// Hashmap implementation -----------------------------------------------------

unsigned long hash(const char* str) 
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned int getValue(char *key, hashmap *map) 
{
    return 0;
}

unsigned int insertValue(char *key, unsigned int value, hashmap *map)
{
    return 0;
}

bool setValue(char *key, unsigned int value, hashmap *map) 
{
    return false;
}

bool deleteValue(char *key, hashmap *map) 
{
    return false;
}

void showMap(hashmap *map)
{
    return;
}

// ----------------------------------------------------------------------------