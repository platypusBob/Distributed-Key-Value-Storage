#include <stdio.h>
#include "utils.h"


int main() 
{
    char *key1 = (char*)calloc(KEY_BYTES, sizeof(char));
    strcpy(key1, "hw:cpu_temp:1710032442");

    float value1 = 42.3;

    kvPair *node1 = initKvPair(key1, value1);

    printf("%s ", node1->key);
    printf("%f", node1->value);
    
    destroyKvPair(node1);

    return 0;
}