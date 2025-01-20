#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

long long gridGame(int** grid, int gridSize, int* gridColSize) {

    printf("\n%i\n", gridSize);

    long long firstRowSum = 0;
    long long secondRowSum = 0;
    long long minSum = LONG_MAX;

    for (int i = 0; i < *gridColSize; i++) {
        firstRowSum += grid[0][i];
    }

    for (int i = 0; i < *gridColSize; i++) {
        firstRowSum -= grid[0][i];
        minSum = MIN(minSum, MAX(firstRowSum, secondRowSum));
        secondRowSum += grid[1][i];
    }

    return minSum;
}

int main() {
    // int grid[2][3] = {{3, 3, 1}, {8, 5, 2}};
    // int grid[2][3] = {{2, 5, 4}, {1, 5, 1}};
    int grid[2][10] = {{20, 3, 20, 17, 2, 12, 15, 17, 4, 15},
                       {20, 10, 13, 14, 15, 5, 2, 3, 14, 3}};
    int* ptrs[2];
    int gridSize = 10;

    for (int i = 0; i < 2; i++) {
        ptrs[i] = grid[i];
    }

    printf("\nresult: %lli\n", gridGame(ptrs, gridSize, &gridSize));

    return 0;
}