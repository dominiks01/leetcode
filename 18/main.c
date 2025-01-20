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

int cmp(const void* a, const void* b) { return *( int* )a - *( int* )b; }

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize,
              int** returnColumnSizes) {

    *returnSize = 0;
    int capacity = 100;
    *returnColumnSizes = malloc(capacity * sizeof(int));

    qsort(nums, numsSize, sizeof(int), cmp);
    int** result = malloc(capacity * sizeof(int*));

    for (int i = 0; i < numsSize; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        for (int j = i + 1; j < numsSize; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            int l = j + 1;
            int p = numsSize - 1;

            while (l < p) {
                long value = ( long )nums[i] + ( long )nums[j] +
                             ( long )nums[l] + ( long )nums[p];

                if (value == ( long )target) {
                    (*returnSize)++;

                    if (*returnSize >= capacity) {
                        capacity *= 2;
                        *returnColumnSizes =
                            realloc(*returnColumnSizes, capacity * sizeof(int));

                        result = realloc(result, capacity * sizeof(int*));
                    }

                    (*returnColumnSizes)[(*returnSize) - 1] = 4;
                    result[*returnSize - 1] = malloc(4 * sizeof(int));
                    result[*returnSize - 1][0] = nums[i];
                    result[*returnSize - 1][1] = nums[j];
                    result[*returnSize - 1][2] = nums[l];
                    result[*returnSize - 1][3] = nums[p];

                    l++;
                    p--;

                    while (l < p && nums[l] == nums[l - 1]) l++;
                    while (l < p && nums[p] == nums[p + 1]) p--;
                } else if (value >= target) {
                    p--;
                } else {
                    l++;
                }
            }
        }
    }

    result = realloc(result, (*returnSize) * sizeof(int*));
    *returnColumnSizes =
        realloc(*returnColumnSizes, (*returnSize) * sizeof(int));

    return result;
}

int main() {

    int nums[] = {1, 0, -1, 0, -2, 2};
    int target = 0;
    int returnSize = 0;
    int* returnColumnSizes = NULL;

    int** result =
        fourSum(&nums[0], 6, target, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < *returnColumnSizes - 1; j++) {
            int value = result[i][j];
            printf("%i,", value);
        }
        printf("%i]\n", result[i][*returnColumnSizes - 1]);
    }

    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}