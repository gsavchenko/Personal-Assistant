#include <stdio.h>
#include <stdlib.h>

// Delete int
void destroyData(void *data);

// Return 0 if equal, 1 if second is larger, -1 if second smaller
int compareData(const void *first, const void *second);

// Display integer data
void printData(void *data);
