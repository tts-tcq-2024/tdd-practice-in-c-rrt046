#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 1000

// Helper function to throw exceptions for negative numbers
static void throw_exception(const char* message, const int* negatives, int count) {
    printf("%s ", message);
    for (int i = 0; i < count; i++) {
        printf("%d ", negatives[i]);
    }
    printf("\n");
    exit(1);
}

// Helper function to split the string by given delimiters
static char** split_string(const char* str, const char* delimiters, int* count) {
    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    
    char** tokens = (char**) malloc(MAX_NUMBERS * sizeof(char*));
    if (tokens == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    char* token = strtok(str_copy, delimiters);
    int index = 0;

    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, delimiters);
    }
    *count = index;
    free(str_copy); // Freeing the duplicated string after use
    return tokens;
}

// Function to validate if a number is negative
static int is_negative(int num) {
    return num < 0;
}

// Function to validate if a number is within the range of 0 to 1000
static int is_within_range(int num) {
    return num <= 1000;
}

// Function to parse custom delimiter from the string
static const char* parse_custom_delimiter(const char* numbers, char* delimiters) {
    const char* num_start = numbers;

    // Check for custom delimiter format
    if (strncmp(numbers, "//", 2) == 0) {
        const char* delim_end = strstr(numbers, "\n");
        int delim_len = delim_end - numbers - 2;
        strncpy(delimiters, numbers + 2, delim_len);
        delimiters[delim_len] = '\0';
        num_start = delim_end + 1;
    }

    return num_start;
}

// Function to calculate the sum of numbers and handle exceptions
int Add(const char* numbers) {
    if (strlen(numbers) == 0) {
        return 0;
    }

    char delimiters[] = ",\n";
    const char* num_start = parse_custom_delimiter(numbers, delimiters);

    int count;
    char** tokens = split_string(num_start, delimiters, &count);

    int sum = 0;
    int negatives[MAX_NUMBERS];
    int neg_count = 0;

    for (int i = 0; i < count; i++) {
        int num = atoi(tokens[i]);
        if (is_negative(num)) {
            negatives[neg_count++] = num;
        } else if (is_within_range(num)) {
            sum += num;
        }
    }

    if (neg_count > 0) {
        throw_exception("negatives not allowed", negatives, neg_count);
    }

    free(tokens); // Freeing the allocated memory for tokens
    return sum;
}

#endif /* STRINGCALCULATOR_H */
