#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define MAP_SIZE 100
#define KEY_BYTES 32


typedef struct kvPair
{
    char *key;
    float value;
    struct kvPair *next;   
} kvPair;

typedef struct hashmap
{
    kvPair *buckets[MAP_SIZE];
    int numActiveItems;
} hashmap;


unsigned long hash(const char* str);

unsigned int getValue(char *key, hashmap *map);

unsigned int insertValue(char *key, float value, hashmap *map);

bool setValue(char *key, float value, hashmap map);

bool deleteValue(char *key, hashmap*map);

void showMap(hashmap *map);

#endif