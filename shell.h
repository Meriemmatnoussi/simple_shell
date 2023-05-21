#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

extern char **environ;

char *_strdup(char *str);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
void free_args(char **args);
void execute_env(void);
char *read_line(void);
void handle_exit(char *line, char **args);
void handle_external_command(char *line, char **args);


#endif
