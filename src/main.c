#include <stdio.h>
#include "utils.h"


    int main() 
    {
        // Creating values

        char key1[KEY_BYTES] = "aa";
        float value1 = 42.1;
        float output1 = 0;

        char key2[KEY_BYTES] = "b@";
        float value2 = 30.1;
        float output2 = 0;

        // Creating the hashmap

        hashmap *map1 = initHashmap();

        if (map1 != NULL)
            printf("Hashmap map1 created successfully\n");
        else
        {
            printf("Failed to create hashmap map1\n");
            return 0;
        }

        printf("-------------------------------\n");

        // Inserting values

        bool set1 = insertValue(key1, value1, map1);

        if (set1)
            printf("SET1 did not return any errors\n");
        else
        {
            printf("SET1 returned an error\n");
            return 0;
        }

        bool set2 = insertValue(key2, value2, map1);

        if (set2)
            printf("SET2 did not return any errors\n");
        else
        {
            printf("SET2 returned an error\n");
            return 0;
        }

        printf("-------------------------------\n");

        // Getting values

        bool get1 = getValue(key1, map1, &output1);

        if (get1)
        {
            printf("GET1 did not return any errors\n");
            printf("Value1 : %f\n", output1);
        }
        else
        {
            printf("GET2 returned an error\n");
            return 0;
        }
            
        bool get2 = getValue(key2, map1, &output2);

        if (get2)
        {
            printf("GET2 did not return any errors\n");
            printf("Value 2 : %f\n", output2);
        }
        else
        {
            printf("GET2 returned an error\n");
            return 0;
        }

        printf("-------------------------------\n");

        // Updating kv2

        bool updt2 = updateValue(key2, 50.1, map1);

        if (updt2)
            printf("Updt2 did not return any errors\n");
        else
            printf("Updt2 returned an error\n");

        bool getUpdate = getValue(key2, map1, &output2);
        printf("New value : %f\n", output2);

        // Cleaning up

        destroyHashmap(map1);
            
        return 0;
    }