#include "shell.h"

void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", _strlen("\n"));
		i++;
	}
}

void handle_exit(char **args, char *line)
{
	free(line);

	if (args)
	{
		int i = 0;

		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}

	exit(0);
}
