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
    if (strncmp(input, "//", 2) == 0) {
        return input[2]; // Custom delimiter specified
    } else {
        return ','; // Default delimiter
    }
}

// Function to parse numbers and calculate sum
void parse_numbers(const char *input, char delimiter, int *sum) {
    char *mutable_input = strdup(input); // Create a mutable copy of input
    char *token;
    char *rest = mutable_input;

    // Skip the optional delimiter definition line if present
    if (strncmp(rest, "//", 2) == 0) {
        strtok_r(rest, "\n", &rest); // Move past the delimiter line
    }

    // Tokenize the rest of the string using the specified delimiter
    while ((token = strtok_r(rest, &delimiter, &rest)) != NULL) {
        int num = atoi(token);
        if (num <= 1000) {
            *sum += num;
        }
    }

    free(mutable_input); // Free the dynamically allocated memory
}

// Function to handle negative numbers
void handle_negatives(const char *input) {
    char *mutable_input = strdup(input); // Create a mutable copy of input
    char *token;
    char *rest = mutable_input;

    while ((token = strtok_r(rest, "\n,", &rest)) != NULL) {
        int num = atoi(token);
        if (num < 0) {
            fprintf(stderr, "negatives not allowed: %d\n", num);
            exit(1);
        }
    }

    free(mutable_input); // Free the dynamically allocated memory
}
