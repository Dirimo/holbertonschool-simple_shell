#include "main.h"

/**
 * execute_command - Handles forking and executing commands.
 * @line: command to execute
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2], *cmd_path;

	args[0] = line;
	args[1] = NULL;

	if (strchr(line, '/'))
		cmd_path = line;
	else
	{
		cmd_path = find_command(line);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", line);
			return;
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);

	if (cmd_path != line)
		free(cmd_path);
}
