#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  /* Include for pid_t */
#include <sys/wait.h>   /* Include for wait() */

/* Function Prototypes */

void exec_command(char *command);


#endif /* SHELL_H */
