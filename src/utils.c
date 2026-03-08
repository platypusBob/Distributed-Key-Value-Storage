/**
*******************************************************************************
* @file : utils.c
* @brief : Implements utilities for the kv-pair storage system.
*******************************************************************************
* This file contains the functions needed to create and manage KV objects and
* hashmaps. 
*
* @author : Matheus Reato B. Piao
* @date : 07 Mar 2026
* @version : 1.0
*******************************************************************************
*/

#include "utils.h"


unsigned long hash(const char* str)   // djb2
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}


kvPair* initKvPair(const char *key, float value) 
{
    kvPair *node = (kvPair*)malloc(sizeof(kvPair));

    if (node == NULL)
        return NULL;

    strncpy(node->key, key, KEY_BYTES - 1);
    node->key[KEY_BYTES - 1] = '\0';

    node->value = value;
    node->next = NULL;

    return node;
}


void destroyKvPair(kvPair *node)
{
    if (node == NULL)
        return;

    free(node);
}


hashmap* initHashmap() 
{
    hashmap *map = (hashmap*)malloc(sizeof(hashmap));

    if (map = NULL)
        return NULL;
    
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map->buckets[i] = NULL;
    }

    return map;
}


void destroyHashmap(hashmap *map) 
{
    if (map == NULL)
        return;
    
    for (int i=0; i<MAP_SIZE; i++) 
    {
        kvPair *current = map->buckets[i];

        while (current!= NULL)
        {
            kvPair *next = current->next;
            free(current);
            current = next;
        }
    }
    
    free(map);
}


float getValue(char *key, hashmap *map) 
{
    return 0;
}


bool insertValue(char *key, float value, hashmap *map)
{
    
}


bool setValue(char *key, float value, hashmap *map) 
{
    return false;
}


void showMap(hashmap *map)
{
    return;
}

