#include "integer.h"

void destroyData(void *data)
{
}

int compareData(const void *first, const void *second)
{
    int one = *((int *)first);
    int two = *((int *)second);

    if (two == one)
        return 0;
    if (two > one)
        return 1;
    return -1;
}

void printData(void *data)
{
    int i = *((int *)data);
    printf("%d\n", i);
}
