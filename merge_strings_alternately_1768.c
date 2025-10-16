#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mergeAlternately(char *, char *);

int main(int argc, char* argv[]) {
    
    char *test1 = mergeAlternately("abc", "def");
    if (strcmp(test1, "adbecf")){
        printf("Test 1 failed: %s\n", test1);
        return 1;
    }
    
    char *test2 = mergeAlternately("abc", "defghi");
    if (strcmp(test2, "adbecfghi")){
        printf("Test 2 failed: %s\n", test2);
        return 1;
    }

    return 0;
}

char* mergeAlternately(char * word1, char * word2){
    // create a counter starting at zero, increment counter each iter
    // take the character at index i and append it to the end of the combined string
    // if index is out of bounds of one string, append the rest of the other string and return

    // allocate memory for a string whose length is the sum of two strings
    size_t totalLength = strlen(word1) + strlen(word2) + 1;
    char *combined = calloc(totalLength, sizeof(char));

    // terminate loop once a sentinel is reached
    for (int i = 0; *word1 && *word2; i++) {
        int currLength = strlen(combined); 
        combined[currLength] = *word1;
        combined[currLength + 1] = *word2;
        word1++;
        word2++;
    }

    if (*word1){
        strcat(combined, word1);
    }
    else if (*word2) {
        strcat(combined, word2);
    }
    else {
        combined[totalLength - 1] = '\0';
    }

    return combined;
}