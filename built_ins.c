#include "library.h"

/**
 * built - checks possible instances for printing and executes
 * the command
 * @head_path: Pointer to head_path of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 * @func_name: is the name how invote the sh
 * @num_cmd: is the number of how many comands it types
 *
 * Return: 0 or what the chosen function returns
 */
int built(struct_path *head_path, char **token, char *buffer, char *func_name,
int num_cmd)
{
	/*int numb = _itoa(token[1]);*/
	int validacion = 0;
	DIR *dir = opendir(token[0]);

	if (dir)
	{
		printError(num_cmd, 1, token[0], func_name);
		closedir(dir);
		return (0);
	}
	if (_strcmp(token[0], "exit") == 0)
	{
		if (token[1] == NULL)
		{
			free(buffer);
			free_list(head_path);
			exitfuncion(token[0]);
		}
		else
			printError(num_cmd, 2, token[1], func_name);
		return (0);
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
	validacion =  built2(token);
	if (validacion == 0)
		return (0);
	return (-1);
}
/**
 * built2 - checks possible instances for printing and executes the command
 * @token: Pointer to tokenized buffer.
 *
 * Return: 0 or what the chosen function returns
 */
int built2(char **token)
{
	if (_strcmp(token[0], "cd") == 0)
	{
		change_the_dir(token);
		return (0);
	}
	else if (_strcmp(token[0], "help") == 0)
	{
		return (0);
	}
	return (-1);
}
/**
 * change_the_dir - is to change the directory
 * @token: Pointer to tokenized buffer.
 *
 * Return: 0 or what the chosen function returns
 */
int change_the_dir(char **token)
{
	char *path = NULL, *current_dir = NULL;

	if (token[1] == NULL || _strcmp(token[1], "~") == 0)
	{
		path = get_path(environ, "HOME");
		chdir(path);
	}
	if (_strcmp(token[1], "-") == 0)
	{
		path = get_path(environ, "OLDPWD");
		chdir(path);
	}
	if (token[1] != NULL)
	{
		chdir(token[1]);
	}

	path = getcwd(current_dir, 100);
	current_dir = get_path(environ, "PWD");
	set_env("OLDPWD", current_dir, environ);
	set_env("PWD", path, environ);
	free(path);
	free(current_dir);

	return (0);
}


/**
 * print_env - prints the environment.
 * @environ: global environment variable.
 *
 * Return: void.
 */
char *print_env(char **environ)
{
	int i;

	if (environ == NULL || *environ == NULL)
	{
		write(1, "not found enviromental variable", 31);
		return (NULL);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 2);
	}

	return (NULL);
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
	exit(127);
}


