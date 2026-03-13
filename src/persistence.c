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

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "persistence.h"


FILE *openLogFile(const char *fileName)
{
    FILE *log = fopen(fileName, "a+");

    if (log == NULL)
    {
        perror("fopen");
        exit(1);
    }

    return log;
}


// Use value = NULL if there is no value argument in the command
void writeToFile(FILE *file, char *command, char *key, float *value)
{
    if (value == NULL)
    {
        fprintf(file, "%s %s\n", command, key);
    }
    else 
    {
        fprintf(file, "%s %s %f\n", command, key, *value);
    }

    fflush(file);
    fsync(fileno(file));
}


void readFile(FILE *file)
{
    return;
}



