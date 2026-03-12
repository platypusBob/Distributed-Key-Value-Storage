/**
*******************************************************************************
* @file : persistence.c
* @brief : Implements persistence for the kv-pair storage system.
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

#include "persistence.h"
#include <stdio.h>
#include <errno.h>


FILE *createLogFile(char *fileName)
{
    FILE *log = fopen(fileName, "a");

    if (log == NULL)
    {
        perror("fopen");
        exit(1);
    }

    return log;
}


void writeToFile(char *command, char *key, float value)
{
    return;
}


void readFile(FILE *file)
{
    return;
}



