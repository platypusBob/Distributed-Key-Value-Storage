/**
*******************************************************************************
* @file : utils.h
* @brief : Declares utilities for the kv-pair storage system.
*******************************************************************************
* This file contains the functions needed to create and manage KV objects and
* hashmaps. 
*
* @author : Matheus Reato B. Piao
* @date : 07 Mar 2026
* @version : 1.0
*******************************************************************************
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAP_SIZE 100
#define KEY_BYTES 32


typedef struct kvPair
{
    char key[KEY_BYTES];
    float value;
    struct kvPair *next;   
} kvPair;


typedef struct hashmap
{
    kvPair *buckets[MAP_SIZE];
    int numActiveItems;
} hashmap;


unsigned long hash(const char* str);

kvPair* initKvPair(const char *key, float value);

void destroyKvPair(kvPair *node);

hashmap* initHashmap();

void destroyHashmap(hashmap *map);

float getValue(char *key, hashmap *map);

bool insertValue(char *key, float value, hashmap *map);

bool setValue(char *key, float value, hashmap *map);

void showMap(hashmap *map);

#endif