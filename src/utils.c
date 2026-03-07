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

    node->key = key;
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


bool initHashmap() 
{
    return false;
}


float getValue(char *key, hashmap *map) 
{
    return 0;
}


bool insertValue(char *key, float value, hashmap *map)
{
    return 0;
}


bool setValue(char *key, float value, hashmap *map) 
{
    return false;
}


void showMap(hashmap *map)
{
    return;
}

