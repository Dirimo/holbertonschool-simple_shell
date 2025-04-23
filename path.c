#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>

char *get_full_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	path = getenv("PATH");
	if (!path)
		return NULL;

	path_copy = _strdup(path);
	if (!path_copy)
		return NULL;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(_strlen(dir) + _strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
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
