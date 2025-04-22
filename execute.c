#include "shell.h"

void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;

	if (!is_executable(args[0]))
	{
		write(STDERR_FILENO, program_name, _strlen(program_name));
		write(STDERR_FILENO, ": ", _strlen(": "));
		write(STDERR_FILENO, "1", _strlen("1"));
		write(STDERR_FILENO, ": ", _strlen(": "));
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", _strlen(": not found\n"));
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
}
