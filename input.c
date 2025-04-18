#include "main.h"

/**
 * handle_input - Prepares and sends input to execution.
 * @line: input string from user
 */
void handle_input(char *line)
{
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	execute_command(line);
}
