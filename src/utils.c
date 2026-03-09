/**
*******************************************************************************
* @file : utils.c
* @brief : Implements utilities for the kv-pair storage system.
*******************************************************************************
* This file contains the functions needed to create and manage KV objects and
* hashmaps. 
*
* @author : Matheus Reato B. Piao
* @date : 08 Mar 2026
* @version : 1.0
*******************************************************************************
*/

#include "utils.h"


// djb2 hash function
unsigned long hash(const char* str)   // djb2
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}


// Initializes a kv pair with the provided key and value
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
    node->active = true;
    node->next = NULL;

    return node;
}


// Frees a kv pair
void destroyKvPair(kvPair *node)
{
    if (node == NULL)
    {
        return;
    }

    free(node);
}

// Initializes a hashmap
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


// Destroys a hashmap
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


// Clears a hashmap (wipes the nodes but keeps the map)
void cleanHashmap(hashmap *map)
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

        map->buckets[i] = NULL;
    }

    map->numActiveItems = 0;
}


// Inserts a node with the provided key and value into the target hashmap
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


// Retrieves the value associated with the provided key
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


// Updates the value associated with the existing key
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


// Deactivates the node associated with the provided key in the target map
// OBS: this function does not free the memory from that node. It only changes
// the node's 'active' attribute to 'false'
void deleteNode(char *key, hashmap *map)
{
    if (key == NULL || map == NULL)
    {
        return;
    }

    unsigned long index = hash(key) % MAP_SIZE;
    kvPair *current = map->buckets[index];

    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0)
        {
            current->active = false;
            return;
        }
            
        current = current->next;
    }

    return;
}


// Traverses the map and prints out every node
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
                printf("Bucket index : %d\n", i);
                printf("Key          : %s\n", current->key);
                printf("Value        : %f\n", current->value);
                printf("Active       : %d\n", current->active);
                printf("--------------------------------------\n");
                printf("\n");

                count++;
                current = current->next;
            }
        }
    }
}

