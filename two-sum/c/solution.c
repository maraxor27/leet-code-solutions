#include <stdlib.h>
#include <stdio.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* solution = malloc(sizeof(int) * 2); 
    *returnSize = 2;
    solution[0] = -1;
    solution[1] = -1;

    int max = -100000;
    int min =  100000;
    for (int i = 0; i < numsSize; i++) {
        if (max < nums[i]) {
            max = nums[i];
        }
        if (min > nums[i]) {
            min = nums[i];
        }
    }

    for (int i = 0; i < (numsSize - 1); i++) {
        // Exit Early
        if (nums[i] + max < target || nums[i] + min > target) {
            printf("Value Range: [%d,%d]\n It is impossible to reach %d with %d\n", min, max, target, nums[i]);
            continue;
        } 

        for (int j = i + 1; j < numsSize; j++) {
            int sub = target - (nums[i] + nums[j]);
            if (sub == 0) { 
                solution[0] = i;
                solution[1] = j;
                return solution;
            }
        }
    }
    return solution;
}