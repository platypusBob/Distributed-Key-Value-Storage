#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define MAX_VALUE 100

typedef struct 
{
    char *key;
    unsigned int value;
    kvPair *nextItem;   // Closed address
} kvPair;

typedef struct 
{
    kvPair *mainArray;
    kvPair *secArray;
    int numActiveItems;
} hashmap;

unsigned long hash(const char* str);

#endif