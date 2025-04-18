#include "main.h"

void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (strchr(args[0], '/'))
		cmd_path = args[0];
	else
	{
		cmd_path = find_command(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
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

	if (cmd_path != args[0])
		free(cmd_path);
}
