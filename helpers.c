#include "shell.h"

/**
 * read_input - Reads a line of input from the user.
 *
 * Return: The input string read from the user.
 */
char *read_input()
{
    char *user_input = NULL;
    size_t bufsize = 0;

    getline(&user_input, &bufsize, stdin);
    return user_input;
}

/**
 * split_input - Splits the input string into an array of tokens.
 * @user_input: The input string to be split.
 *
 * Return: An array of tokens.
 */
char **split_input(char *user_input)
{
    int token_bufsize = TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(token_bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(user_input, TOKEN_DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= token_bufsize)
        {
            token_bufsize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, token_bufsize * sizeof(char *));
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
