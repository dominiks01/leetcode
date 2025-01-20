#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **highestPeak(int **isWater, int isWaterSize, int *isWaterColSize,
                  int *returnSize, int **returnColumnSizes) {
    const int m = isWaterSize;
    const int n = isWaterColSize[0];

    int row[5 * m * n];
    int col[5 * m * n];
    int val[5 * m * n];

    int lo = 0, hi = 0;

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (isWater[r][c]) {
                row[hi] = r;
                col[hi] = c;
                val[hi] = 0;

                ++hi;

                isWater[r][c] = -1;
            } else {
                isWater[r][c] = INT_MAX;
            }
        }
    }

    const int dirs[][2] = {{-1, 0}, {+1, 0}, {0, +1}, {0, -1}};

    while (lo < hi) {
        const int r = row[lo];
        const int c = col[lo];
        const int v = val[lo];

        ++lo;

        if (!(-1 < r && r < m)) continue;
        if (!(-1 < c && c < n)) continue;

        if (isWater[r][c] == -1) {
            isWater[r][c] = 0;

            for (int d = 0; d < 4; ++d) {
                row[hi] = r + dirs[d][0];
                col[hi] = c + dirs[d][1];
                val[hi] = 1;

                ++hi;
            }
        }

        if (isWater[r][c] > v) {
            isWater[r][c] = v;

            for (int d = 0; d < 4; ++d) {
                row[hi] = r + dirs[d][0];
                col[hi] = c + dirs[d][1];
                val[hi] = v + 1;

                ++hi;
            }
        }
    }

    *returnSize = isWaterSize;
    *returnColumnSizes = isWaterColSize;

    return isWater;
}
int main() {

    int **isWater = malloc(sizeof(int *));
    int isWaterSize = 3;
    int isWaterColSize = 3;

    for (int i = 0; i < isWaterSize; i++) {
        isWater[i] = malloc(sizeof(int) * isWaterColSize);
    }

    int isWaterTmp[3][3] = {{0, 0, 1}, {1, 0, 0}, {0, 0, 0}};
    for (int i = 0; i < isWaterSize; i++) {
        for (int j = 0; j < isWaterColSize; j++) {
            isWater[i][j] = isWaterTmp[i][j];
        }
    }

    printf("-------------\n");
    for (int i = 0; i < isWaterSize; i++) {
        for (int j = 0; j < isWaterColSize; j++) {
            printf("%i ", isWater[i][j]);
        }
        printf("\n");
    }

    printf("-------------");

    int returnSize = 0;
    int **returnColumSizes = NULL;
    int **res = highestPeak(isWater, isWaterSize, &isWaterColSize, &returnSize,
                            returnColumSizes);

    for (int i = 0; i < isWaterSize; i++) {
        free(isWater[i]);
        free(res[i]);
    }
    free(isWater);
    free(res);

    //
    return 0;
}