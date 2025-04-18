#include "main.h"

/**
 * main - Simple shell that executes a single-word command.
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	struct stat sb;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Ctrl+D */
		{
			printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0') /* Ligne vide */
			continue;

		/* Vérifier si le fichier existe */
		if (stat(line, &sb) == -1)
		{
			perror(line);
			continue;
		}

		execute_command(line);
	}

	free(line);
	return (0);
}

/**
 * execute_command - Fork and exec a command.
 * @line: command to execute
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = line;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

