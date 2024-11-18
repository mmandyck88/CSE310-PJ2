#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "heap.h"
#include "util.h"

int main(int argc, char** argv) {
    FILE* fp, * outFile;
    HEAP* pHeap;
    ELEMENT** V;
    int n, index;
    double key;
    char Word[100];  

    // Checks for correct argument usage
    if (argc != 3) {
        fprintf(stderr, "Usage: ./PJ2 <I-File> <O-File>\n");
        exit(1);
    }

    // Open input file checksfor errors
    fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open input file %s\n", argv[1]);
        exit(1);
    }

    // Reads number of elements
    fscanf(fp, "%d", &n);

    // Allocate V and pHeap memory
    V = (ELEMENT**)malloc((n + 1) * sizeof(ELEMENT*));
    pHeap = (HEAP*)malloc(sizeof(HEAP));
    pHeap->capacity = n;
    pHeap->size = 0;  // Initially the heap is empty
    pHeap->H = (int*)malloc((n + 1) * sizeof(int));

    // Read element keys and initialize elements
    for (int i = 1; i <= n; i++) {
        V[i] = (ELEMENT*)malloc(sizeof(ELEMENT));
        fscanf(fp, "%lf", &V[i]->key);
        V[i]->index = i;
        V[i]->pos = 0;  // Initially not in the heap
    }

    fclose(fp);  // Closes input file

    // Opens output writing file
    outFile = fopen(argv[2], "w");
    if (!outFile) {
        fprintf(stderr, "Error: cannot open output file %s\n", argv[2]);
        exit(1);
    }

    // Main loop handles instructions
    while (scanf("%s", Word) != EOF) {
        if (strcmp(Word, "Read") == 0) {
            printf("Instruction: Read\n");
        }

        if (strcmp(Word, "PrintArray") == 0) {
            printf("Instruction: PrintArray\n");
            
            for (int i = 1; i <= n; i++) {
                printf("%d %.6lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
            }
        }

        if (strcmp(Word, "PrintHeap") == 0) {
            printf("Instruction: PrintHeap\n");
            printf("Capacity = %d, size = %d\n", pHeap->capacity, pHeap->size);

            // Print heap details according to the current size
            for (int i = 1; i <= pHeap->size; i++) {
                printf("H[%d] = %d\n", i, pHeap->H[i]);
            }
        }

        if (strcmp(Word, "Insert") == 0) {
            // Prompts index to insert
            scanf("%d", &index);
            // Check index validity
            if (index >= 1 && index <= n) {
                // Check if the element is already in the heap
                if (V[index]->pos == 0) {
                    printf("Instruction: Insert %d\n", index);
                    printf("Element V[%d] inserted into the heap\n", index);

                    // Inserts element to heap
                    pHeap->size++;
                    // Sets position in heap array
                    pHeap->H[pHeap->size] = index;
                    V[index]->pos = pHeap->size;

                    // Performs heapify-up to maintain min-heap
                    int i = pHeap->size;
                    while (i > 1) {
                        int parent = i / 2;
                        if (V[pHeap->H[parent]]->key > V[pHeap->H[i]]->key) {
                            // Swap positions in `H` array if out of order
                            int temp = pHeap->H[parent];
                            pHeap->H[parent] = pHeap->H[i];
                            pHeap->H[i] = temp;

                            // Update positions in the `V` array
                            V[pHeap->H[parent]]->pos = parent;
                            V[pHeap->H[i]]->pos = i;

                            // Move up to the parent
                            i = parent;
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    // If element already in heap, print instruction only
                    printf("Instruction: Insert %d\n", index);
                }
            }
            else {
                // If index is invalid, do nothing
                printf("Instruction: Insert %d\n", index);
            }
        }

        if (strcmp(Word, "BuildHeap") == 0) {
            printf("Instruction: BuildHeap\n");
            pHeap->size = n;
            // Initializes heap array & all elements
            for (int i = 1; i <= n; i++) {
                pHeap->H[i] = i;
                V[i]->pos = i;
            }
            // Performs heapify-down operation for non-leaf nodes
            for (int i = n / 2; i >= 1; i--) {
                int current = i;
                while (2 * current <= pHeap->size) {
                    int left = 2 * current;
                    int right = left + 1;
                    int smallest = current;

                    if (left <= pHeap->size && V[pHeap->H[left]]->key < V[pHeap->H[smallest]]->key) {
                        smallest = left;
                    }
                    if (right <= pHeap->size && V[pHeap->H[right]]->key < V[pHeap->H[smallest]]->key) {
                        smallest = right;
                    }
                    if (smallest != current) {
                        // Swap positions
                        int temp = pHeap->H[current];
                        pHeap->H[current] = pHeap->H[smallest];
                        pHeap->H[smallest] = temp;

                        // Updates V positions
                        V[pHeap->H[current]]->pos = current;
                        V[pHeap->H[smallest]]->pos = smallest;

                        current = smallest;
                    }
                    else {
                        break;
                    }
                }
            }
        }

        if (strcmp(Word, "DecreaseKey") == 0) {
            // Read value of index and new key 
            scanf("%d %lf", &index, &key);

            if (index < 1 || index > n || V[index]->pos == 0) {
                // Invalid index or element not in the heap
                printf("Instruction: DecreaseKey %d %.6lf\n", index, key);
                continue;
            }

            // Prints decrease key
            printf("Instruction: DecreaseKey %d %.6lf\n", index, key);

            // Updates key value
            V[index]->key = key;

            // Performs heapify-up operation & restores heap property
            int i = V[index]->pos;
            while (i > 1) {
                int parent = i / 2;
                if (V[pHeap->H[parent]]->key > V[pHeap->H[i]]->key) {
                    // If out of order Swap positions in `H` array 
                    int temp = pHeap->H[parent];
                    pHeap->H[parent] = pHeap->H[i];
                    pHeap->H[i] = temp;

                    // Updates `V` array positions 
                    V[pHeap->H[parent]]->pos = parent;
                    V[pHeap->H[i]]->pos = i;

                    // Move up to parent
                    i = parent;
                }
                else {
                    break;
                }
            }
        
        }

        if (strcmp(Word, "ExtractMin") == 0) {
            if (pHeap->size == 0) {
                printf("Instruction: ExtractMin\n");
                continue; // If the heap is empty, skip this
            }
            printf("Instruction: ExtractMin\n");

            // Removes minimum element (root)
            int minIndex = pHeap->H[1];
            V[minIndex]->pos = 0;  // Mark removed from heap
            pHeap->H[1] = pHeap->H[pHeap->size];
            V[pHeap->H[1]]->pos = 1;
            pHeap->size--;

            // Performs heapify-down operation & restores min-heap property
            int current = 1;
            while (2 * current <= pHeap->size) {
                int left = 2 * current;
                int right = left + 1;
                int smallest = current;

                if (left <= pHeap->size && V[pHeap->H[left]]->key < V[pHeap->H[smallest]]->key) {
                    smallest = left;
                }
                if (right <= pHeap->size && V[pHeap->H[right]]->key < V[pHeap->H[smallest]]->key) {
                    smallest = right;
                }
                if (smallest != current) {
                    // Swap positions
                    int temp = pHeap->H[current];
                    pHeap->H[current] = pHeap->H[smallest];
                    pHeap->H[smallest] = temp;

                    // Update V positions
                    V[pHeap->H[current]]->pos = current;
                    V[pHeap->H[smallest]]->pos = smallest;

                    current = smallest;
                }
                else {
                    break;
                }
            }
        }

        if (strcmp(Word, "Write") == 0) {
            printf("Instruction: Write\n");
            // Writes array contents to output file
            for (int i = 1; i <= n; i++) {
                fprintf(outFile, "%d %.6lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
            }
        }

        if (strcmp(Word, "Stop") == 0) {
            printf("Instruction: Stop\n");
            break; 
        }
    }

    // Closes output file
    fclose(outFile);

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        free(V[i]);
    }
    free(V);
    free(pHeap->H);
    free(pHeap);

    return 0;
}
