#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
<<<<<<< HEAD

// Assuming get_full_path is defined in path.c and declared in shell.h
extern char *get_full_path(char *command);

void execute_command(char **args, char *program_name) {
	char *command = args[0];
	char *full_path = get_full_path(command);

	if (full_path == NULL) {
		fprintf(stderr, "%s: %s: command not found\n", program_name, command);
		return; // Do NOT fork
	}

	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		free(full_path);
		return;
	}

	if (pid == 0) {
		// Child process
		if (execve(full_path, args, environ) == -1) {
			perror("execve");
			free(full_path); // Free before exiting in child
			exit(EXIT_FAILURE); // Important: exit in the child process on execve failure
		}
	} else {
		// Parent process
		int status;
		wait(&status);
		free(full_path); // Free the allocated path after the child process is done
	}
=======
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * execute_command - exécute une commande dans un nouveau processus
 * @args: tableau d'arguments (commande + arguments)
 * @program_name: nom du programme principal (argv[0]) pour les messages d'erreur
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path = NULL;
	struct stat st;

	if (strchr(args[0], '/'))
	{
		if (stat(args[0], &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			command_path = _strdup(args[0]);
	}
	else
	{
		command_path = get_full_path(args[0]);
	}

	if (!command_path)
	{
		fprintf(stderr, "%s: %s: not found\n", program_name, args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror(command_path);
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}

	free(command_path);
>>>>>>> refs/remotes/origin/main
}
