#include "utils.h"
#include "persistence.h"

#define BUFFER_SIZE 256

int main()
{
    // Initializing the map ---------------------------------------------------

    hashmap *map1 = initHashmap();

    if (map1 == NULL)
    {
        printf("Hashmap init failed\n");
        return 0;
    }


    // Initiating the log file and replaying the commands ---------------------

    FILE *logFile = openLogFile("log.aof");
    rewind(logFile);
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, logFile))
    {
        char *commandRead = strtok(buffer, " \n");
        char *keyRead = strtok(NULL, " \n");
        char *valueStrRead = strtok(NULL, " \n");

        if (commandRead == NULL)
        {
            continue;
        }
        
        if (strcmp(commandRead, "SET") == 0)
        {
            if (keyRead && valueStrRead)
            {
                float valueRead = strtof(valueStrRead, NULL);
                float outputRead = 0;

                if (getValue(keyRead, map1, &outputRead))
                {
                    bool opStatusRead = updateValue(keyRead, valueRead, map1);
                }
                else
                {
                    bool opStatusRead = insertValue(keyRead, valueRead, map1);
                }
            }
        }
        else if (strcmp(commandRead, "DEL") == 0)
        {
            if (keyRead) 
            {
                deleteNode(keyRead, map1);
            }
        }
        else
        {
            continue;
        }
    }


    // CLI --------------------------------------------------------------------

    printf("\n");
    printf("--------------------------------\n");
    printf("---------- KVPlatypus ----------\n");
    printf("--------------------------------\n");
    printf("\n");

    char input[BUFFER_SIZE];

    while (true)
    {
        printf("-- KVPlayupus --> ");

        if (fgets(input, BUFFER_SIZE, stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = 0; // Remove \n
        char *command = strtok(input, " ");

        if (strcmp(input, "QUIT") == 0)
        {
            printf("\n");
            break;
        }
        else if (strcmp(input, "HELP") == 0)
        {
            printf("\n");
            printf("----------- COMMANDS -----------\n");
            printf("\n");
            printf("GET <key>         : returns the value associated with <key>\n");
            printf("SET <key> <value> : sets <key>'s value to <value>\n");
            printf("  Attention: if <key> already exists, SET updates it.\n");
            printf("SHOW       : prints out the individual nodes\n");
            printf("DEL <key>         : deactivates <key>\n");
            printf("\n");
        }
        else if (strcmp(command, "GET") == 0)
        {
            char *key = strtok(NULL, " ");
            float output = 0;

            bool opStatus = getValue(key, map1, &output);
            

            if (!opStatus)
            {
                printf("\n");
                printf("Operation failed. Key might not exist or be deactivated.\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("--------------------------------\n");
                printf("Key   : %s\n", key);
                printf("Value : %f\n", output);
                printf("--------------------------------\n");
                printf("\n");
            }
        }
        else if (strcmp(command, "SET") == 0)
        {
            char *key = strtok(NULL, " ");
            char *valueStr = strtok(NULL, " ");
            float value = strtof(valueStr, NULL);
            float output = 0;
            bool opStatus = false;
            bool update; // true if the value was updated, false if inserted.

            if (key && valueStr)
            {
                if (getValue(key, map1, &output))
                {
                    opStatus = updateValue(key, value, map1);
                    update = true;
                }
                else
                {
                    opStatus = insertValue(key, value, map1);
                    update = false;
                }
            }
            else
            {
                printf("\n");
                printf("Usage: SET <key> <value>\n");
                printf("\n");

                continue;
            }

            if (opStatus)
            {
                writeToFile(logFile, command, key, &value);
                
                if (update)
                {
                    printf("\n");
                    printf("--------------------------------\n");
                    printf("Updated value %f for key %s\n", value, key);
                    printf("--------------------------------\n");
                    printf("\n");
                }
                else
                {
                    printf("\n");
                    printf("--------------------------------\n");
                    printf("Inserted value %f for key %s\n", value, key);
                    printf("--------------------------------\n");
                    printf("\n");
                }
            }
            else
            {
                printf("\n");
                printf("Operation failed.\n");
                printf("\n");
            }
        }
        else if (strcmp(command, "DEL") == 0)
        {
            char *key = strtok(NULL, " ");
            deleteNode(key, map1);
            writeToFile(logFile, command, key, NULL);

            printf("\n");
            printf("--------------------------------\n");
            printf("Key %s deactivated\n", key);
            printf("--------------------------------\n");
            printf("\n");
        }
        else if (strcmp(command, "SHOW") == 0)
        {
            printf("\n");
            showMap(map1);
        }
        else
        {
            printf("\n");
            printf("Invalid command\n");
            printf("\n");
        }
    }

    destroyHashmap(map1);

    return 0;
}