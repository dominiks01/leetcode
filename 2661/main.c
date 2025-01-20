#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/hash_map.h"
#include "../utils/pair.h"

char* int_to_str(int num, char* buffer) {
    char* ptr = buffer;
    if (num < 0) {
        *ptr++ = '-';
        num = -num;
    }

    char* start = ptr;
    do {
        *ptr++ = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    *ptr = '\0';

    for (char* end = ptr - 1; start < end; start++, end--) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
    }
    return buffer;
}

int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize,
                       int* matColSize) {

    HashMap* pairs_map = hash_map_create();

    char str[10];

    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[i]; j++) {
            int_to_str(mat[i][j], str);
            pair new_pair = {.first = i, .second = j};
            hash_map_insert(pairs_map, str, &new_pair, sizeof(pair));
        }
    }

    int cols_result[matColSize[0]] = {};
    int rows_result[matSize] = {};

    for (int i = 0; i < arrSize; i++) {
        snprintf(str, 10, "%i", arr[i]);
        pair* act = hash_map_find(pairs_map, str);

        cols_result[act->second]++;
        if (cols_result[act->second] >= matSize) {
            hash_map_free(pairs_map);
            free(pairs_map);
            return i;
        }

        rows_result[act->first]++;
        if (rows_result[act->first] >= matColSize[0]) {
            hash_map_free(pairs_map);
            free(pairs_map);
            return i;
        }
    }

    for (int i = 0; i < matSize; i++) {
        printf("%i", matColSize[i]);
    }

    hash_map_free(pairs_map);
    free(pairs_map);
    return 0;
}

int main() {

    int arr[] = {6, 2, 3, 1, 4, 5};
    int arrSize = 6;
    int matSize = 3;
    int matColSize[] = {2, 2, 2};

    int* ptrs[3];
    int mat[3][2] = {{5, 1}, {2, 4}, {6, 3}};

    for (int i = 0; i < matSize; i++) {
        ptrs[i] = mat[i];
    }

    int result =
        firstCompleteIndex(&arr[0], arrSize, ptrs, matSize, &matColSize[0]);

    printf("%i\n", result);

    return 0;
}