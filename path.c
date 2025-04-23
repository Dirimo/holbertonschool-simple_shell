#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* get_full_path - find the full path of a command using the PATH variable */
char *get_full_path(char *command)
{
	char *path = NULL, *path_copy = NULL, *dir, *full_path;
	struct stat st;

	if (strchr(command, '/'))
		return NULL;

	path = getenv("PATH");
	if (!path)
		path = "/usr/local/bin:/usr/bin:/bin";

	path_copy = _strdup(path);
	if (!path_copy)
		return NULL;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		size_t len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		snprintf(full_path, len, "%s/%s", dir, command);

		if (stat(full_path, &st) == 0 &&
		    S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
