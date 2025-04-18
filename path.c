#include "main.h"

/**
 * find_command - Searches for a command in the PATH.
 * @command: command name (e.g., ls)
 * Return: full path if found, NULL otherwise
 */
char *find_command(char *command)
{
	char *path = getenv("PATH");
	char *token, *full_path;
	struct stat st;

	if (!path)
		return (NULL);

	path = strdup(path);
	token = strtok(path, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
			return (NULL);

		sprintf(full_path, "%s/%s", token, command);

		if (stat(full_path, &st) == 0)
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
