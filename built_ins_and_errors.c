#include "library.h"

/**
 * built - checks possible instances for printing and executes
 * the command
 * @head_path: Pointer to head_path of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 *
 * Return: 0 or what the chosen function returns
 */
int built(struct_path *head_path, char **token, char *buffer)
{
	if (_strcmp(token[0], "exit") == 0)
	{
/* a token dos hay que transformarlo en un numero*/
		free(buffer);
		free_list(head_path);
		exitfuncion(token[0]);
	}
	else if (_strcmp(token[0], "env") == 0)
	{
		if (token[1] == NULL)
		{
			print_env(environ);
			return (0);
		}
		write(1, "env: ", 5);
		write(1, token[1], _strlen(token[1]));
		write(1, ": No such file or directory", 27);
		write(1, "\n", 1);
		return (0);
	}

	return (-1);
}

/**
 * get_path - finds and stores environmental variable PATH.
 * @environ: global environment variable.
 * @direccion: global variable to store (PATH in this case).
 *
 * Return: full path or NULL if it fails.
 */
char *get_path(char **environ, char *direccion)
{
	int i = 0, validacion = 0;
	char *token = NULL, *full_path = NULL, *env = NULL;

	for (i = 0; environ[i]; i++)
	{
		env = malloc(_strlen(environ[i]) + 1);
		_strcpy(env, environ[i]);
		token = strtok(env, "=");
		validacion = _strcmp(env, direccion);
		if (validacion == 0)
		{
			token = strtok(NULL, "=");
			if (token)
			{
				full_path = malloc(_strlen(token) + 1);
				_strcpy(full_path, token);
				free(env);
				return (full_path);
			}
			else
				return (NULL);
		}
		free(env);
		token = NULL;
	}
	perror("Error : not found the enviromental variables - path");
	return (NULL);
}

/**
 * print_env - prints the environment.
 * @environ: global environment variable.
 *
 * Return: void.
 */
void print_env(char **environ)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 2);
	}
}

/**
 * printError - it will print the error
 * @validacion: to choose what kind of error print
 * @num_cmd: is the counter to track how many fails it appear
 * @command: the command it has to try
 * @func_name: prints what was typed by user ans is causing errors.
 */
void printError(int num_cmd, int validacion, char *command,  char *func_name)
{
	char *num_str = pitoa(num_cmd);
	/* validacion == 0 significa que no va encontrar el comando */
	if (validacion == 0)
	{
		write(1, func_name, _strlen(func_name));
		/* aca va el pitoa que convierte de numero a string*/
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": not found", 11);
		write(1, "\n", 1);
		free(num_str);
	}
	if (validacion == 1)
	{
		write(1, func_name, _strlen(func_name));
		/* aca va el pitoa que convierte de numero a string*/
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": Permission denied", 20);
		write(1, "\n", 1);
		free(num_str);
	}
}
