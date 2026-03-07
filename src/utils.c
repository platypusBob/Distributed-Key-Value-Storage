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


bool initHashmap() 
{

}

unsigned int getValue(char *key, hashmap *map) 
{
    return 0;
}

unsigned int insertValue(char *key, float value, hashmap *map)
{
    return 0;
}

bool setValue(char *key, float value, hashmap *map) 
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