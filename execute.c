
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		command_path = _strdup(args[0]);
	}
	else
	{
		command_path = get_full_path(args[0]);
	}

	if (!command_path)
	{
		write(STDERR_FILENO, program_name, _strlen(program_name));
		write(STDERR_FILENO, ": command not found\n", 20);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	free(command_path);
}
