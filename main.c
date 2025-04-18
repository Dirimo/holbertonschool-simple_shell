#include "shell.h"

char **environ;

int main(int argc, char **argv, char **env) {
    char *command;
    char **args;

    (void)argc;
    (void)argv;

    environ = env;

    while (1) {
        display_prompt();
        command = read_command();

        if (command == NULL) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (command[0] == '\0' || command[0] == '\n') {
            free(command);
            continue;
        }

        args = tokenize_command(command);
        execute_command(args);

        free(command);
        free(args);
    }

    return 0;
}
