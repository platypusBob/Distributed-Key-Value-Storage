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
    kvPair *node = malloc(sizeof(kvPair));

    if (node == NULL)
    {
        return NULL;
    }

    strncpy(node->key, key, KEY_BYTES - 1);
    node->key[KEY_BYTES - 1] = '\0';

    node->value = value;
    node->next = NULL;

    return node;
}


void destroyKvPair(kvPair *node)
{
    if (node == NULL)
    {
        return;
    }

    free(node);
}


hashmap* initHashmap() 
{
    hashmap *map = malloc(sizeof(hashmap));

    if (map == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map->buckets[i] = NULL;
    }

    map->numActiveItems = 0;

    return map;
}


void destroyHashmap(hashmap *map) 
{
    if (map == NULL)
    {
        return;
    }
    
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


void cleanHashmap(hashmap *map)
{
    return;
}


bool insertValue(char *key, float value, hashmap *map)
{
    // Keys are assumed to be unique because they include timestamps.
    // Therefore this function does not check for duplicates.
    
    if (map == NULL || key == NULL)
    {
        return false;
    }

    unsigned long index = hash(key) % MAP_SIZE;

    kvPair *newNode = initKvPair(key, value);

    if (newNode == NULL)
    {
        return false;
    }

    kvPair *current = map->buckets[index];

    if (current == NULL)
    {
        map->buckets[index] = newNode;
        map->numActiveItems++;
        return true;
    }
    else 
    {
        while (current->next != NULL) 
        {
            current = current->next;
        }

        current->next = newNode;
        map->numActiveItems++;
        return true;
    }
}


bool getValue(char *key, hashmap *map, float *output) 
{
    if (map == NULL || key == NULL)
    {
        return false;
    }

    unsigned long index = hash(key) % MAP_SIZE;
    kvPair *current = map->buckets[index];
    
    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0)
        {
            *output = current->value;
            return true;
        }
            
        current = current->next;
    }

    return false;
}


bool updateValue(char *key, float newValue, hashmap *map) 
{
    if (key == NULL || map == NULL)
    {
        return false;
    }

    unsigned long index = hash(key) % MAP_SIZE;
    kvPair *current = map->buckets[index];

    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = newValue;
            return true;
        }
            
        current = current->next;
    }

    return false;
}


void showMap(hashmap *map)
{
    if (map == NULL)
    {
        printf("Argument 'map' is invalid\n");
        return;
    }

    int count = 1;
    printf("---------- HASHMAP OVERVIEW ----------\n");
    printf("Active items : %d\n", map->numActiveItems);
    printf("\n");

    for (int i=0; i<MAP_SIZE; i++)
    {
        if (map->buckets[i] != NULL)
        {
            kvPair *current = map->buckets[i];

            while (current != NULL)
            {
                printf("--------------- NODE %d ---------------\n", count);
                printf("Key   : %s\n", current->key);
                printf("Value : %f\n", current->value);
                printf("--------------------------------------\n");
                printf("\n");

                count++;
                current = current->next;
            }
        }
    }
}

