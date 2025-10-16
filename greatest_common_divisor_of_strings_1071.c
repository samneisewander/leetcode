#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Psuedocode
/*
        smaller problem: how do find a substring that divides one of the given strings?

        work from big to small
            - ABC ABC ABC
        know for this that the string divides itself, so that is the initial condition

        if the string has even length, next largest tilable subdivision is its length divided by 2
        else if odd, next largest tilable subdivision is 3

        strlen() / 2 # if its even you just divide by two each time

        strlen() / 3 # if its odd, you just divide by three each time

        11111 22222 33333 44444 55555

        ^ so for this, largest is 15, then 5, then 1

        if not cleanly divisible by 2 or 3, 1 is the largest subdivision (string of 1 repeating character)

        easy to check if a potential subdivision works: just compare using strstr, advance pointer, then compare again
        if you get all the way to the end without a null pointer, then it works.

        - strcmp to see if equal, early termination
        - find which string is shorter, apply algo to short string
        - use str str to check if it divides both strings. if so, return. otherwise, chop small string and repeat.


        failed case;

        so for odd numbers we have a tricky problem... 

        TAUXXTAUXXTAUXXTAUXXTAUXX
        TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX
        
        start with strlen(divisor) / 2, that chops the string in half
        TAUXXTAUXXTA UXXTAUXXTAUXX

        then take new len and see if it divides original string. if not, decrement by one until it does

*/

// Function Prototypes
int min(int a, int b);
char* gcdOfStrings(char*, char*);
bool checkStringDivisible(const char*, const char*);
int gcd(int, int);

// Main
int main(int argc, char* argv[]){
    
    // Test 1
    char* test1 = gcdOfStrings("abc", "abc");
    if (strcmp(test1, "abc")){
        printf("Test failed: Expected \"abc\", got \"%s\".", test1);
        return 1;
    }
    
    char* test2 = gcdOfStrings("abc", "abcabc");
    if (strcmp(test2, "abc")){
        printf("Test failed: Expected \"abc\", got \"%s\".", test2);
        return 1;
    }
    free(test2);
    
    char* test3 = gcdOfStrings("abcabc", "abcd");
    if (strcmp(test3, "")){
        printf("Test failed: Expected \"\", got \"%s\".", test3);
        return 1;
    }
    
    char* test4 = gcdOfStrings("aaa", "aaaaa");
    if (strcmp(test4, "a")){
        printf("Test failed: Expected \"a\", got \"%s\".", test4);
        return 1;
    }
    free(test4);

    char* test5 = gcdOfStrings("TAUXXTAUXXTAUXXTAUXXTAUXX", "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX");
    if (strcmp(test5, "TAUXX")){
        printf("Test failed: Expected \"TAUXX\", got \"%s\".", test5);
        return 1;
    }
    free(test5);

    return 0;

}

// Function Definitions

// atempt three (really fast success)
char* gcdOfStrings(char* str1, char* str2) {

    // get gcd of lengths of strings
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int gcdOfLengths = str1Len < str2Len ? str1Len : str2Len;
    
    while (gcdOfLengths > 1) {
        if (str1Len % gcdOfLengths == 0 && str2Len % gcdOfLengths == 0) {
            break;
        }
        gcdOfLengths--;
    }

    char divisor[gcdOfLengths + 1];
    
    strncpy(divisor, str1Len < str2Len ? str1 : str2, gcdOfLengths);
    divisor[gcdOfLengths] = '\0';
    
    if (checkStringDivisible(str1, divisor) && checkStringDivisible(str2, divisor)) {
        char* result = calloc(strlen(divisor) + 1, sizeof(char));
        strcpy(result, divisor);
        return result;
    }
    
    return "";
    
}

// attempt two (success)
char* gcdOfStrings(char* str1, char* str2) {
    
    // Guard null pointers
    if (!str1 || !str2){
        return NULL;
    }

    if (strcmp(str1, str2) == 0) {
        return str1;
    }

    // get gcd of lengths of strings
    int gcdOfLengths = gcd(strlen(str1), strlen(str2));
    
    char divisor[BUFSIZ];
    
    strncpy(divisor, strlen(str1) < strlen(str2) ? str1 : str2, BUFSIZ);
    divisor[gcdOfLengths] = '\0';
    
    if (checkStringDivisible(str1, divisor) && checkStringDivisible(str2, divisor)) {
        char* result = calloc(strlen(divisor) + 1, sizeof(char));
        strcpy(result, divisor);
        return result;
    }
    
    return "";
}

bool checkStringDivisible(const char* dividend, const char* divisor) {
    // if the lengths arent divisible, the strings must not be.
    size_t divisorLength = strlen(divisor);
    if (strlen(dividend) % divisorLength > 0){
        return false;
    }

    // walk through dividend until terminator reached or string does not divide
    while (*dividend){
        char* matchPosition = strstr(dividend, divisor);
        if (matchPosition && matchPosition == dividend){
            dividend += divisorLength;
        }
        else {
            return false;
        }
    }
    return true;
}

int gcd(int a, int b) {
    int small = min(a , b);

    while (small > 1) {
        if (a % small == 0 && b % small == 0) {
            return small;
        }
        small--;
    }

    return 1;
}

/***
 * Returns the smaller of integers a, b, or a if they are the same.
 */
int min(int a, int b){
    return (a <= b) ? a : b;
}

// attempt one
// char* gcdOfStrings(char* str1, char* str2) {
    
//     // Guard null pointers
//     if (!str1 || !str2){
//         return NULL;
//     }

//     if (strcmp(str1, str2) == 0) {
//         return str1;
//     }

//     size_t divisorLength = min(strlen(str1), strlen(str2));
//     // buffer overflow vulnerability if passed strings are very large?

//     // Initialize divisor to shorter of two strings. Cap buffer size at BUFSIZ
//     char currDivisor[divisorLength + 1];
//     char* dividend = NULL;

//     if (strlen(str1) == divisorLength){
//         strcpy(currDivisor, str1);
//         dividend = str2;
//     }
//     else {
//         strcpy(currDivisor, str2); 
//         dividend = str1;
//     }
    
//     while (divisorLength > 1){
//         if (checkStringDivisible(dividend, currDivisor)) {
//             char* gcd = calloc(strlen(currDivisor) + 1, sizeof(char));
//             strcpy(gcd, currDivisor);
//             return gcd;
//         }

//         // If the current divisor is not the GCD, reduce it to its first half (if even) or third (if odd).
//         // If the divisor's length is not divisible by 2 or 3, reduce it to its first character.
//         if (divisorLength % 2 == 0) {
//             divisorLength /= 2;
//         }
//         else if (divisorLength % 2 == 1) {
//             divisorLength /= 3;
//         }
//         else {
//             divisorLength = 1;
//         }

//         currDivisor[divisorLength] = '\0';
//     }

//     // Check the condition where the GCD is a single character
//     if (checkStringDivisible(dividend, currDivisor)) {
//         char* gcd = calloc(strlen(currDivisor) + 1, sizeof(char));
//         strcpy(gcd, currDivisor);
//         return gcd;
//     }
    
//     return "";
// }