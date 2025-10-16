#include <stdbool.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    // need discover threshold
    // need sort? no. just need know largets candies value.
    

    // log(n) time complexity, log(n) space complexity
    // march to find largest candies
    // calculate threshold
    // march through array and compare to threshold

    int mostCandies = 0;
    *returnSize = candiesSize;

    for (int i = 0; i < candiesSize; i++) {
        if (mostCandies < candies[i]) {
            mostCandies = candies[i];
        }
    }

    int threshold = mostCandies - extraCandies;
    bool* result = malloc(candiesSize * sizeof(bool));

    for (int i = 0; i < candiesSize; i++) {
        if (candies[i] >= threshold) {
            result[i] = true;
        }
        else {
            result[i] = false;
        }
    }

    return result;
}