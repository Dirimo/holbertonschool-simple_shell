#include "main.h"

/**
 * handle_input - Prepares and sends input to execution.
 * @line: input string from user
 */
void handle_input(char *line)
{
	char **args;
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	args = tokenize_input(line);
	if (args[0] != NULL)

	execute_command(args);
	
	free(args);
}
