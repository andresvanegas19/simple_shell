#include "library.h"

/**
 * verificarbuffer - checks if buffer receives bothersome characters.
 * @buffer: buffer containing what was printed by user.
 * @validar: ammount of chars in buffer.
 * @func_name: name of function to print in errors.
 * @num_cmd: to print the number of errors in document so far.
 * Return: 0 or -1 if it fails.
 */
int verificarbuffer(char *buffer, int validar, char *func_name, int num_cmd)
{
	char losnulos[5] = {' ', '\n', '.', '\t'};
	int i = 0, j = 0, error = 0, punto = 0;

	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '.')
			punto++;
		for (j = 0; j < 5; j++)
		{
			if (buffer[i] == losnulos[j])
				error++;
		}
	}

	if (error == validar)
	{
		i -= 1;
		buffer[i] = '\0';
		if (punto == 2)
			printError(num_cmd, 1, buffer, func_name);
		else if (punto >= 2)
			printError(num_cmd, 0, buffer, func_name);
		return (-1);
	}
	return (0);
}

/**
 * support_magic - checks possible instances for printing and execute avoid the
 *  problem whit the path
 * @token: Pointer to result.
 *
 * Return: 0 or what the chosen function returns
 */
int support_magic(char **token)
{
	char raiz[5] = "/bin/";
	struct stat st;
	int i;

/* If there is a /bin/something, it executes it */
	for (i = 0; raiz[i] == (*token)[i] && i < 5; i++)
	{
		if (i == 4)
			if (access(token[0], F_OK | X_OK) == 0)
				if (stat(token[0], &st) == 0 && st.st_mode & S_IXUSR)
				{
					command(token[0], token, environ);
					return (0);
				}
	}
/* Checks if what is received is a ./something type executable */
	if (((*token)[0] == '.' && (*token)[1] == '/'))
	{
/* Check if the file exists and use the bitwise to check is executable*/
		if (stat(token[0], &st) == 0 && st.st_mode & S_IXUSR)
			command(token[0], token, environ);
		return (0);
	}
	return (-1);
}

/**
 * exitfuncion - exits.
 * @signal: is the satus of the exit
 *
 * Return: void.
 */
void exitfuncion(char *signal)
{
	(void) signal;
	exit(0);
}

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
