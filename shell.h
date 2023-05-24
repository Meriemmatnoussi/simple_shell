#ifndef SHELL_H
#define SHELL_H

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_input();
char **split_input(char *input);
void shell_loop();
int execute(char **args);

#endif
