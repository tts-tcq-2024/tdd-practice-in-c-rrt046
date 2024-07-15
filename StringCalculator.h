#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
int add(const char *input);
char parse_delimiter(const char *input);
char parse_custom_delimiter(const char *input);
char parse_default_delimiter(const char *input);
void parse_and_sum_numbers(char *token, int *sum);
void parse_numbers(const char *input, char delimiter, int *sum);
void handle_negatives(const char *input);

// Function to add numbers as per StringCalculator requirements
int add(const char *input) {
    if (input == NULL || strlen(input) == 0)
        return 0;

    char delimiter = parse_delimiter(input);
    int sum = 0;
    parse_numbers(input, delimiter, &sum);
    handle_negatives(input);

    return sum;
}

// Function to parse the delimiter from input string
char parse_delimiter(const char *input) {
    if (strncmp(input, "//", 2) == 0) {
        return parse_custom_delimiter(input);
    } else {
        return parse_default_delimiter(input);
    }
}

// Function to parse custom delimiter from input string
char parse_custom_delimiter(const char *input) {
    const char *delimiter_start = strchr(input, '[');
    if (delimiter_start != NULL) {
        const char *delimiter_end = strchr(delimiter_start + 1, ']');
        if (delimiter_end != NULL) {
            int delimiter_length = delimiter_end - delimiter_start - 1;
            char custom_delimiter[delimiter_length + 1];
            strncpy(custom_delimiter, delimiter_start + 1, delimiter_length);
            custom_delimiter[delimiter_length] = '\0';
            return custom_delimiter[0];
        }
    }
    return input[2];
}

// Function to parse default delimiter from input string
char parse_default_delimiter(const char *input) {
    return input[2];
}

// Function to parse numbers from tokenized input and calculate sum
void parse_and_sum_numbers(char *token, int *sum) {
    int num = atoi(token);
    if (num <= 1000) {
        *sum += num;
    }
}

// Function to parse numbers and calculate sum
void parse_numbers(const char *input, char delimiter, int *sum) {
    char *mutable_input = strdup(input); // Create a mutable copy of input
    char *rest = mutable_input;
    char *token;

    // Skip the optional delimiter definition line if present
    if (strncmp(rest, "//", 2) == 0) {
        strtok_r(rest, "\n", &rest); // Move past the delimiter line
    }

    // Tokenize the rest of the string using the specified delimiter
    while ((token = strtok_r(rest, &delimiter, &rest)) != NULL) {
        parse_and_sum_numbers(token, sum);
    }

    free(mutable_input); // Free the dynamically allocated memory
}

// Function to handle negative numbers
void handle_negatives(const char *input) {
    char *token, *rest;
    char *mutable_input = strdup(input); // Create a mutable copy of input

    rest = mutable_input;

    while ((token = strtok_r(rest, "\n,", &rest)) != NULL) {
        int num = atoi(token);
        if (num < 0) {
            fprintf(stderr, "negatives not allowed: %d\n", num);
            exit(1);
        }
    }

    free(mutable_input); // Free the dynamically allocated memory
}

#endif // STRING_CALCULATOR_H
