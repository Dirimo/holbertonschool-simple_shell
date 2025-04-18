#include "shell.h"

/**
 * execute_builtin - Executes a built-in command.
 * @args: An array of strings containing the command and
 * its arguments.
 *
 * Return: 1 if the command is a built-in and was executed,
 * 0 otherwise.
 */
int execute_builtin(char **args) {
    if (args == NULL || args[0] == NULL) {
        return 0;
    }

    if (strcmp(args[0], "env") == 0) {
        
        extern char **environ;
        char **env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        
        exit(0);
        return (1);
    }

    return (0);
}

/**
 * execute_command - Executes a command.
 *
 * @args: An array of strings containing the command
 * and its arguments.
 */
void execute_command(char **args) {
    pid_t pid;
    int status;
    char error_message[256];

    if (args == NULL || args[0] == NULL) {
        return;
    }

    /* Check if it's a built-in command */
    if (execute_builtin(args)) {
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        /* Child process */
        execve(args[0], args, environ);

        /* If execve fails */
        snprintf(error_message, sizeof(error_message),
	 "%s: No such file or directory\n", args[0]);
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(&status);
    }
}
