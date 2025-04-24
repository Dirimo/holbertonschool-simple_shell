#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
}
