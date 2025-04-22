#include "shell.h"

/**
 * display_prompt - affiche le prompt dans le shell
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
