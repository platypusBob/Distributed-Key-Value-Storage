/**
*******************************************************************************
* @file : persistence.h
* @brief : Declares persistence for the kv-pair storage system.
*******************************************************************************
* This file contains the functions needed to implement append-only persistence
* to the operation of the kv-pair storage system. A log file is created and 
* each command is appended to it on the fly. When the system restarts, it reads
* through the log file to rebuild the hashmap.
*
* @author : Matheus Reato B. Piao
* @date : 12 Mar 2026
* @version : 1.0
*******************************************************************************
*/

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdio.h>


FILE *openLogFile(const char *fileName);

// Use value = -1.0 if there's no valua argument in the command
void writeToFile(FILE *file, char *command, char *key, float *value);

void readFile(FILE *file);

#endif