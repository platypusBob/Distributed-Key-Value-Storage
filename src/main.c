#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int main() 
{
    char name1[] = "Matheus";
    char name2[] = "Mateus";

    unsigned long hash1 = hash(name1);
    unsigned long hash2 = hash(name2);

    printf("%lu\n", hash1);
    printf("%lu\n", hash2);
}