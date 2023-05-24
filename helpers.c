#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Read input from stdin and return a dynamically allocated string.
 *
 * This function reads a line of input from
 * the standard input (stdin) and returns
 * the input as a dynamically allocated string.
 * The caller is responsible for freeing
 * the allocated memory when it is no longer needed.
 *
 * @return The input string read from stdin.
 * The caller is responsible for freeing the allocated memory.
 */
char *read_input()
{
    char *input = NULL;
    size_t bufsize = 0;
    getline(&input, &bufsize, stdin);
    return input;
}

/**
 * Splits the input string into an array of tokens based on delimiters.
 *
 * @param input The input string to be split.
 * @return The array of tokens. The last element in the array is set to NULL.
 *         The caller is responsible for freeing the allocated memory.
 */
char **split_input(char *input)
{
    int bufsize = TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}
