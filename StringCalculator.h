#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function declarations
int add(const char* input);
int extractNumbersAndSum(const char* input, char delimiter);
bool hasCustomDelimiter(const char* input, char* delimiter);
const char* movePastCustomDelimiter(const char* input);

// Function to add numbers from a string input
int add(const char* input) {
    if (input == NULL || *input == '\0')
        return 0;

    char delimiter = ',';
    if (hasCustomDelimiter(input, &delimiter)) {
        input = movePastCustomDelimiter(input);
    }

    return extractNumbersAndSum(input, delimiter);
}

// Helper function to extract numbers from input and compute sum
int extractNumbersAndSum(const char* input, char delimiter) {
    int sum = 0;
    char buffer[strlen(input) + 1];
    strcpy(buffer, input);

    char* token = strtok(buffer, ",\n");
    while (token != NULL) {
        int number = atoi(token);
        if (number <= 1000)
            sum += number;
        token = strtok(NULL, ",\n");
    }

    return sum;
}

// Helper function to check for custom delimiter
bool hasCustomDelimiter(const char* input, char* delimiter) {
    if (input[0] == '/' && input[1] == '/') {
        *delimiter = input[2];
        return true;
    }
    return false;
}

// Helper function to move past the custom delimiter declaration
const char* movePastCustomDelimiter(const char* input) {
    return input + 3;
}

#endif // STRINGCALCULATOR_H
