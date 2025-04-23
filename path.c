#include "shell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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

    if (strchr(command, '/')) {
        if (stat(command, &st) == 0) {
            if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
                return _strdup(command);
            }
            errno = EACCES;
        }
        perror(command);
        return NULL;
    }

    path = getenv("PATH");
    if (!path) path = "/usr/local/bin:/usr/bin:/bin";

    path_copy = _strdup(path);
    if (!path_copy) return NULL;

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

        if (stat(full_path, &st) == 0)
        {
            if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
            {
                free(path_copy);
                return full_path;
            }
            errno = EACCES;
            free(full_path);
        }
        else
        {
            free(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    fprintf(stderr, "%s: command not found\n", command);
    return NULL;
}
