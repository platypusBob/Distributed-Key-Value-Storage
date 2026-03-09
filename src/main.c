#include "utils.h"

#define BUFFER_SIZE 256

int main()
{
    hashmap *map1 = initHashmap();

    if (map1 == NULL)
    {
        printf("Hashmap init failed\n");
        return 0;
    }

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

            if (key && value)
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

            printf("\n");
            printf("--------------------------------\n");
            printf("Key %s deactivated\N", key);
            printf("--------------------------------\n");
            printf("\n");
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