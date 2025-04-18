#include "main.h"

/**
 * find_command - Searches for a command in the PATH.
 * @command: command name (e.g., ls)
 * Return: full path if found, NULL otherwise
 */
char *_path(char *str)
{
	struct stat st;
	int i;
	char *path = _getenv("PATH");
	char **tab_path = split_env(path);
	char *newpath = malloc(sizeof(char) *1024);

	if (newpath == NULL)
	{
		perror("Failed malloc");
		return (NULL);
	}
	for (i = 0; tab_path[i] != NULL; i++)
	{
		newpath[0] = 0;
		_strcat(newpath, tab_path[i]);
		_strcat(newpath, "/");
		_strcat(newpath, str);
		if(stat(newpath,&st) == 0)
			return(newpath);
	}
	free(newpath);
	return (NULL);
}
