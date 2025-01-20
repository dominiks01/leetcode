#include <complex.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) { return *( int* )a - *( int* )b; }

int threeSumClosest(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int result = 0;
    int distance = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int k = i + 1;
        int j = numsSize - 1;

        while (k < j) {
            int value = nums[i] + nums[j] + nums[k];
            if (abs(value - target) < distance) {
                distance = abs(value - target);
                result = value;
            }

            if (value > target) {
                j--;
            } else if (value < target) {
                k++;
            } else if (value == target) {
                return value;
            }
        }
    }

    return result;
}

int main() {

    int nums[] = {0, 1, 2};
    int target = 3;
    int numsSize = 3;

    int result = threeSumClosest(&nums[0], numsSize, target);

    printf("%i\n", result);
    return 0;
}