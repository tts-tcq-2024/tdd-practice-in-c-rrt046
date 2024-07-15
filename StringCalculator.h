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

// Function to parse custom delimiter from the string
static const char* parse_custom_delimiter(const char* numbers, char* delimiters) {
    const char* num_start = numbers;

    if (strncmp(numbers, "//", 2) == 0) {
        const char* delim_end = strstr(numbers, "\n");
        int delim_len = delim_end - numbers - 2;
        strncpy(delimiters, numbers + 2, delim_len);
        delimiters[delim_len] = '\0';
        num_start = delim_end + 1;
    }

    return num_start;
}

// Function to validate if a number is negative
static int is_negative(int num) {
    return num < 0;
}

// Function to validate if a number is within the range of 0 to 1000
static int is_within_range(int num) {
    return num <= 1000;
}

// Function to tokenize the string
static int tokenize_string(const char* str, const char* delimiters, char** tokens) {
    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    char* token = strtok(str_copy, delimiters);
    int count = 0;

    while (token != NULL) {
        tokens[count++] = token;
        token = strtok(NULL, delimiters);
    }

    free(str_copy);
    return count;
}

// Function to process a single token
static int process_token(const char* token, int* negatives, int* neg_count) {
    int num = atoi(token);
    if (is_negative(num)) {
        negatives[(*neg_count)++] = num;
        return 0;
    } else if (is_within_range(num)) {
        return num;
    }
    return 0;
}

// Function to process tokens and calculate the sum
static int process_tokens(char** tokens, int count, int* negatives, int* neg_count) {
    int sum = 0;

    for (int i = 0; i < count; i++) {
        sum += process_token(tokens[i], negatives, neg_count);
    }

    return sum;
}

// Function to calculate the sum of numbers and handle exceptions
int add(const char* numbers) {
    if (strlen(numbers) == 0) {
        return 0;
    }

    char delimiters[100] = ",\n";
    const char* num_start = parse_custom_delimiter(numbers, delimiters);

    char* tokens[MAX_NUMBERS];
    int count = tokenize_string(num_start, delimiters, tokens);

    int negatives[MAX_NUMBERS];
    int neg_count = 0;

    int sum = process_tokens(tokens, count, negatives, &neg_count);

    if (neg_count > 0) {
        throw_exception("negatives not allowed", negatives, neg_count);
    }

    return sum;
}

#endif /* STRINGCALCULATOR_H */
