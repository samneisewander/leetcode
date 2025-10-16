#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* reverseWords(char* s) {
    if (!s) {
        return NULL;
    }

    // the sky is blue

    size_t bufferSize = strlen(s) + 2;

    char* outBuf = calloc(bufferSize, sizeof(char));
    char tmpBuf[bufferSize];

    tmpBuf[0] = '\0';
    char* tok = strtok(s, " ");

    while(tok){
        strcpy(tmpBuf, tok);
        strcat(tmpBuf, " ");
        strcat(tmpBuf, outBuf);
        strcpy(outBuf, tmpBuf);

        tok = strtok(NULL, " ");
    }

    outBuf[strlen(outBuf) - 1] = '\0';

    return outBuf;
}

char* fastReverseWords(char* s){
    size_t inSize = strlen(s);
    size_t bufferSize = inSize + 2;
    char* head = s + inSize;
    char delimiter = ' ';
    char* outBuf = calloc(bufferSize, sizeof(char));

    /**
     * start at end
     * decrement until hit delimiter
     * set character to null
     * everything in front gets added to output
     * 
     * 
     */

    while(head - s > 0) {
        if (*head == delimiter) {
            *head = '\0';

            if (strlen(head + 1) > 0) {
                strcat(outBuf, head + 1);
                strcat(outBuf, " ");
            }
        }
        head--;
    }

    if (*head == delimiter) {
        strcat(outBuf, head + 1);
        size_t finalSize = strlen(outBuf);
        if (outBuf[finalSize - 1] == delimiter) {
            outBuf[finalSize - 1] = '\0';
        }
    }
    else {
        strcat(outBuf, head);
    }

    return outBuf;

}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return 1;
    }

    char* input = argv[1];
    char* output = fastReverseWords(input);

    printf("Reversed: %s\n", output);

    if (output){
        free(output);
    }

    return 0;
}