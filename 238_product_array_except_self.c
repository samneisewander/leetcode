#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// This problem has to do with prefix and suffix sums... using auxilliary arrays to get results.

/**
 * A prefix sum is the array containing the cumulative sums of all array elements up to
 * and including the ith element. A suffix sum is the same but in reverse.
 * 
 * For this problem you have to compute the prefix and suffix PRODUCTS, and then
 * multiply the prefix product to the left of each ith element with the suffix product
 * to the right. Elegant solution that requires an evasive trick that no one would
 * naturally think of.
 * 
 */

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int prefixProduct = 1;
    int suffixProduct = 1;
    int prefixProductArr[numsSize];
    int suffixProductArr[numsSize];
    int* returnArr = malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        prefixProduct *= nums[i];
        prefixProductArr[i] = prefixProduct;
        suffixProduct *= nums[numsSize - 1 - i];
        suffixProductArr[numsSize - 1 - i] = suffixProduct;
    }

    for (int i = 0; i < numsSize; i++) {
        // Handle edge of array conditions
        if (i <= 0) {
            returnArr[i] = suffixProductArr[i + 1];
        }
        else if (i >= numsSize - 1) {
            returnArr[i] = prefixProductArr[i - 1];
        }
        // Handle internal conditions
        else {
            returnArr[i] = prefixProductArr[i - 1] * suffixProductArr[i + 1];
        }
    }

    return returnArr;

    // 1  2  3  4   In
    // 1  2  6  24  Prefix
    // 24 24 12 4   Suffix
    // 24 12 8  6   Out
}

int main(int argc, char* argv[]) {

    int test1[] = {1,2,3,4};

    int returnSize;
    int *results = productExceptSelf(test1, 4, &returnSize);

    printf("In: ");

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", test1[i]);
    }
    
    printf("\nOut: ");

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", results[i]);
    }

    return 0;
}