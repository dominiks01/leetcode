#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countServers(int** grid, int gridSize, int* gridColSize) {

    int col_count[*gridColSize] = {};
    int row_count[gridSize] = {};
    int result = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] == 1) {
                col_count[j]++;
                row_count[i]++;
            }
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] != 1) {
                continue;
            }

            if (((col_count[j] > 1 && row_count[i] != 0) ||
                 (col_count[j] != 0 && row_count[i] > 1))) {
                result++;
            }
        }
    }

    return result;
}

int main() {

    int array[2][2] = {{1, 0}, {1, 1}};
    int gridSize = 2;
    int gridColSize = 2;

    int** ptr = malloc(sizeof(int*) * gridSize);

    for (int i = 0; i < gridSize; i++) {
        ptr[i] = array[i];
    }

    printf("\nresult: %i\n", countServers(ptr, gridSize, &gridColSize));

    return 0;
}