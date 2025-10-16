#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isVowel(char);

char* reverseVowels(char*);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return 1;
    }

    char* input = argv[1];

    printf("Reversed: %s\n", reverseVowels(input));

    return 0;
}

char* reverseVowels(char* s) {
    char* start = s;
    char* end = s + strlen(s);

    // "cccccccccc"

    while (end - start > 0) {
        // advance left until vowel found. if terminator reached, break.
        while (*start && !isVowel(*start)) {
            start++;
        }

        // advance right until vowel found. if start of string reached, break.
        while (end - s >= 0 && !isVowel(*end)) {
            end--;
        }

        // if the pointers cross, break.
        if (end - start <= 0) {
            break;
        }

        else {
            // valid swap found. swap.
            char tmp = *end;
            *end = *start;
            *start = tmp;
            start++;
            end--;
        }
    }

    return s;
}

bool isVowel(char c){
    return (
        c == 'a' ||
        c == 'A' ||
        c == 'e' ||
        c == 'E' ||
        c == 'i' ||
        c == 'I' ||
        c == 'o' ||
        c == 'O' ||
        c == 'u' ||
        c == 'U'
    );
}