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
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAP_SIZE 100
#define KEY_BYTES 32


typedef struct kvPair   // Node size = 44 bytes
{
    char key[KEY_BYTES];
    float value;
    bool active;
    struct kvPair *next;   
} kvPair;


typedef struct hashmap   // Size = 4 + (MAP_SIZE * 44) bytes
{
    kvPair *buckets[MAP_SIZE];
    int numActiveItems;
    // Map is an array of heads of linked lists.
} hashmap;


unsigned long hash(const char* str);

kvPair* initKvPair(const char *key, float value);

void destroyKvPair(kvPair *node);

void cleanHashmap(hashmap *map);

hashmap* initHashmap();

void destroyHashmap(hashmap *map);

bool insertValue(char *key, float value, hashmap *map);

bool getValue(char *key, hashmap *map, float *output);

bool updateValue(char *key, float newValue, hashmap *map);

void deleteNode(char *key, hashmap *map);

void showMap(hashmap *map);

#endif