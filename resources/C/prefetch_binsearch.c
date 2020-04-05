/* In a given example __builtin_prefetch is used to pre fetch some of the data to cache to reduce cache misses
 * NOTE: pre fetching data that remains unused is called "cache pollution".
 *
 * __builtin_prefetch (&array[(mid + 1 + high)/2], 0, 1);
 *                                                 |  |_ rw
 *                                                 |____ locality
 *
 *  rw:         - compile time constant
 *      rw=1 - prefetch is preparing for a write to the memory address
 *      rw=0 (default) - prefetch is preparing for read from the memory address
 *
 *  locality:   - compile time constant, values between 0 and 3
 *      locality=0 - data has no temporal locality (not needed to be left in cache after the success
 *      locality=3 (default) - data has highest level of temporal locality (stays as long as possible)
 *
 * Code credits goes to Igor Zhirkov, author of book "Low-Level Programming"
 */


#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024*512*16

static int DO_PREFETCH = 0;

int binarySearch(int *array, size_t number_of_elements, int key) {
    size_t low = 0;
    size_t high = number_of_elements - 1;
    size_t mid = 0;
    while(low <= high) {
        mid = (low + high) / 2;
        if (DO_PREFETCH){
            //low path
            __builtin_prefetch (&array[(mid + 1 + high)/2], 0, 1);
            // high patch
            __builtin_prefetch (&array[(low - mid - 1)/2], 0, 1);
        }
        if (array[mid] < key)
            low = mid + 1;
        else if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            high = mid - 1;
    }
    return -1;
}

int main() {
    char *prefetch = getenv("DO_PREFETCH");
    if (prefetch != NULL) DO_PREFETCH = 1;
    size_t i = 0;
    int NUM_LOOKUPS = SIZE;
    int *array;
    int *lookups;
    srand(time(NULL));
    array = malloc(SIZE * sizeof(int));

    lookups = malloc(NUM_LOOKUPS * sizeof(int));

    for (i = 0; i < SIZE; i++ ) array[i] = i;
    for (i - 0; i < NUM_LOOKUPS; i++) lookups[i] = rand() % SIZE;

    for (i = 0; i < NUM_LOOKUPS; i++) binarySearch(array, SIZE, lookups[i]);

    free(array);
    free(lookups);

    return 0;
}
