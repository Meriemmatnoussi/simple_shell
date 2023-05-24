#include "shell.h"

char *read_input()
{
    char *input = NULL;
    size_t bufsize = 0;
    getline(&input, &bufsize, stdin);
    return input;
}

char **split_input(char *input)
{
    int bufsize = TOKEN_BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}
