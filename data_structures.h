#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct TAG_ELEMENT {
    int index;   // index element
    double key;  // key value of element
    int pos;     // index in heap array, 0 if not in heap
} ELEMENT;

typedef struct TAG_HEAP {
    int capacity;   // capacity of heap
    int size;       // current size of heap
    int* H;         // array of pointers to indices of the ELEMENT array
    ELEMENT** V;    // array of pointers to ELEMENT
} HEAP;

#endif
