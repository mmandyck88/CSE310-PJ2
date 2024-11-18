#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Heapify function
void Heapify(HEAP* pHeap, int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;

    if (left <= pHeap->size && pHeap->V[pHeap->H[left]]->key < pHeap->V[pHeap->H[smallest]]->key) {
        smallest = left;
    }

    if (right <= pHeap->size && pHeap->V[pHeap->H[right]]->key < pHeap->V[pHeap->H[smallest]]->key) {
        smallest = right;
    }

    if (smallest != i) {
        // Swap elements
        int temp = pHeap->H[i];
        pHeap->H[i] = pHeap->H[smallest];
        pHeap->H[smallest] = temp;

        // Update positions
        pHeap->V[pHeap->H[i]]->pos = i;
        pHeap->V[pHeap->H[smallest]]->pos = smallest;

        Heapify(pHeap, smallest);
    }
}

// BuildHeap function
void BuildHeap(HEAP* pHeap) {
    for (int i = pHeap->size / 2; i >= 1; i--) {
        Heapify(pHeap, i);
    }
}

// ExtractMin function
ELEMENT* ExtractMin(HEAP* pHeap) {
    if (pHeap->size < 1) {
        printf("Error: heap is empty\n");
        return NULL;
    }

    ELEMENT* minElement = pHeap->V[pHeap->H[1]];
    pHeap->H[1] = pHeap->H[pHeap->size];
    pHeap->size--;
    Heapify(pHeap, 1);

    return minElement;
}

// Insert function
void Insert(HEAP* pHeap, int index) {
    if (pHeap->V[index]->pos != 0) {
        printf("Error: V[%d] already in the heap\n", index);
        return;
    }

    if (pHeap->size == pHeap->capacity) {
        printf("Error: heap overflow\n");
        return;
    }

    pHeap->size++;
    pHeap->H[pHeap->size] = index;
    pHeap->V[index]->pos = pHeap->size;

    int i = pHeap->size;
    while (i > 1 && pHeap->V[pHeap->H[i]]->key < pHeap->V[pHeap->H[i / 2]]->key) {
        // Swap elements
        int temp = pHeap->H[i];
        pHeap->H[i] = pHeap->H[i / 2];
        pHeap->H[i / 2] = temp;

        // Updates positions
        pHeap->V[pHeap->H[i]]->pos = i;
        pHeap->V[pHeap->H[i / 2]]->pos = i / 2;

        i = i / 2;
    }
}

// DecreaseKey function
void DecreaseKey(HEAP* pHeap, int index, double newKey) {
    if (newKey > pHeap->V[index]->key) {
        printf("Error: invalid call to DecreaseKey\n");
        return;
    }

    pHeap->V[index]->key = newKey;
    int i = pHeap->V[index]->pos;

    while (i > 1 && pHeap->V[pHeap->H[i]]->key < pHeap->V[pHeap->H[i / 2]]->key) {
        // Swap elements
        int temp = pHeap->H[i];
        pHeap->H[i] = pHeap->H[i / 2];
        pHeap->H[i / 2] = temp;

        // Update positions
        pHeap->V[pHeap->H[i]]->pos = i;
        pHeap->V[pHeap->H[i / 2]]->pos = i / 2;

        i = i / 2;
    }
}

// PrintHeap function
void PrintHeap(HEAP* pHeap) {
    if (pHeap == NULL) {
        printf("Error: heap is NULL\n");
        return;
    }

    for (int i = 1; i <= pHeap->size; i++) {
        printf("Element with index %d and key %.2lf at position %d\n",
            pHeap->H[i], pHeap->V[pHeap->H[i]]->key, pHeap->V[pHeap->H[i]]->pos);
    }
}

// PrintArray function
void PrintArray(ELEMENT** V, int size) {
    if (V == NULL) {
        printf("Error: array is NULL\n");
        return;
    }

    for (int i = 1; i <= size; i++) {
        printf("%d %.2lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
    }
}
