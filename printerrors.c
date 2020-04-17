#include "library.h"
/**
 * manejar_signal - supresses use of ctrl - c.
 * @valor: value sent by signal.
 *
 * Return: void.
 */
void manejar_signal(int valor)
{
	(void) valor;
	write(STDOUT_FILENO, "\nShellOfDoom$ ", _strlen("\nShellOfDoom$ "));
}

/**
 * printError - it will print the error
 * @validacion: to choose what kind of error print
 * @num_cmd: is the counter to track how many fails it appear
 * @command: the command it has to try
 * @func_name: prints what was typed by user ans is causing errors.
 */
int printError(int num_cmd, int validacion, char *command,  char *func_name)
{
	char *num_str = pitoa(num_cmd);

	if (validacion == 0)
	{
		write(1, func_name, _strlen(func_name));
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": not found", 11);
		write(1, "\n", 1);
		free(num_str);
		return (100);
	}
	if (validacion == 1)
	{
		write(1, func_name, _strlen(func_name));
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": Permission denied", 20);
		write(1, "\n", 1);
		free(num_str);
		return (100);
	}
	if (validacion == 2)
	{
		write(1, func_name, _strlen(func_name));
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": exit:", 7);
		write(1, " Illegal number: ", 17);
		write(1, command, _strlen(command));
		write(1, "\n", 1);
		free(num_str);
		return (100);
	}
	return (100);
}

/**
 * printError2 - it will print the error
 * @num_cmd: is the counter to track how many fails it appear
 * @func_name: prints what was typed by user ans is causing errors.
 *
 */
void printError2(int num_cmd,  char *func_name)
{
	char *num_str = pitoa(num_cmd);

	write(1, func_name, _strlen(func_name));
	write(1, ": ", 2);
	write(1, num_str, _strlen(num_str));
	write(1, ": .: .: not found", 17);
	write(1, "\n", 1);
	free(num_str);
}
