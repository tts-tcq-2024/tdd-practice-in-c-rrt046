#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
int add(const char *input);
char parse_delimiter(const char *input);
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
    char delimiter = ',';
    if (strncmp(input, "//", 2) == 0) {
        const char *delimiter_start = strchr(input, '[');
        if (delimiter_start != NULL) {
            const char *delimiter_end = strchr(delimiter_start + 1, ']');
            if (delimiter_end != NULL) {
                int delimiter_length = delimiter_end - delimiter_start - 1;
                char custom_delimiter[delimiter_length + 1];
                strncpy(custom_delimiter, delimiter_start + 1, delimiter_length);
                custom_delimiter[delimiter_length] = '\0';
                delimiter = custom_delimiter[0];
            }
        } else {
            delimiter = input[2];
        }
    }
    return delimiter;
}

// Function to parse numbers and calculate sum
void parse_numbers(const char *input, char delimiter, int *sum) {
    char *token, *rest = (char *) input;

    while ((token = strtok_r(rest, "\n,", &rest)) != NULL) {
        int num = atoi(token);
        if (num <= 1000) {
            *sum += num;
        }
    }
}

// Function to handle negative numbers
void handle_negatives(const char *input) {
    char *token, *rest = (char *) input;

    while ((token = strtok_r(rest, "\n,", &rest)) != NULL) {
        int num = atoi(token);
        if (num < 0) {
            fprintf(stderr, "negatives not allowed: %d\n", num);
            exit(1);
        }
    }
}

#endif // STRING_CALCULATOR_H
