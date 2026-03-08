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

        // Inserting values

        bool set1 = insertValue(key1, value1, map1);

        bool set2 = insertValue(key2, value2, map1);

        // Getting values

        bool get1 = getValue(key1, map1, &output1);
            
        bool get2 = getValue(key2, map1, &output2);

        // Updating kv2

        bool updt2 = updateValue(key2, 50.1, map1);

        // Show

        showMap(map1);

        // Cleaning up

        destroyHashmap(map1);
            
        return 0;
    }