#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "shell.h"
#include "helpers.h"

void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        print_prompt();
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);
}

int execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            // Change directory to the value of HOME environment variable
            const char *home_dir = getenv("HOME");
            if (home_dir == NULL) {
                fprintf(stderr, "shell: cd: HOME not set\n");
            } else {
                if (chdir(home_dir) != 0) {
                    perror("shell");
                }
            }
        } else if (strcmp(args[1], "-") == 0) {
            // Change directory to the value of OLDPWD environment variable
            const char *old_pwd = getenv("OLDPWD");
            if (old_pwd == NULL) {
                fprintf(stderr, "shell: cd: OLDPWD not set\n");
            } else {
                if (chdir(old_pwd) != 0) {
                    perror("shell");
                }
            }
        } else {
            // Change directory to the specified directory
            if (chdir(args[1]) != 0) {
                perror("shell");
            }
        }
        // Update the value of PWD environment variable
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            setenv("PWD", cwd, 1);
        } else {
            perror("shell");
        }
        return 1;
    }

    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
