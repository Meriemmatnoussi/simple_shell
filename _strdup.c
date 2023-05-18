#include "shell.h"

/**
 * _strdup - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: The pointer to the newly allocated duplicated string
 */
char *_strdup(char *str)
{
	char *dup;
	size_t len;
	size_t i;

	if (str == NULL)
		return (NULL);

	len = strlen(str) + 1;
	dup = malloc(len * sizeof(char));
	if (dup == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < len; i++)
	{
		dup[i] = str[i];
	}

	return (dup);
}
