#include "util.h"
#include <stdio.h>
#include <string.h>

int nextInstruction(char* Word, int* index, double* key) {
    int returnV;

    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop") == 0) return 1;
    if (strcmp(Word, "PrintArray") == 0) return 1;
    if (strcmp(Word, "PrintHeap") == 0) return 1;
    if (strcmp(Word, "BuildHeap") == 0) return 1;
    if (strcmp(Word, "ExtractMin") == 0) return 1;

    if (strcmp(Word, "Insert") == 0) {
        returnV = fscanf(stdin, "%d", index);
        return returnV == 1;
    }

    if (strcmp(Word, "DecreaseKey") == 0) {
        returnV = fscanf(stdin, "%d %lf", index, key);
        return returnV == 2;
    }

    return 0;
}
