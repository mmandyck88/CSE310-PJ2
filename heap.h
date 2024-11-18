#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

// Function declarations for heap operations
void BuildHeap(HEAP* pHeap);
void Heapify(HEAP* pHeap, int i);
ELEMENT* ExtractMin(HEAP* pHeap);
void Insert(HEAP* pHeap, int index);
void DecreaseKey(HEAP* pHeap, int index, double newKey);
void PrintHeap(HEAP* pHeap);
void PrintArray(ELEMENT** V, int size);

#endif
