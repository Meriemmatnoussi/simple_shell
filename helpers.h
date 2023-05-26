#ifndef HELPERS_H
#define HELPERS_H

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

void print_prompt(void);
char *read_line(void);
char **split_line(char *line);

#endif /* HELPERS_H */
