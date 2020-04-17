#include "library.h"

/**
 * basic_commands - opens space in memory and allocates directions of
 * basic commands.
 * @comando: command to execute.
 * @head_path: pointer to first element in singly linked list.
 * @func_name: name of function.
 * @num_cmd: times prompt has been executed.
 *
 * Return: Null.
 */
char *basic_commands(char *comando, struct_path *head_path, char *func_name,
		     int num_cmd)
{
	struct stat st;
	char *path_cmd = NULL;

	while (head_path->next)
	{
		path_cmd = malloc((_strlen(head_path->str) + _strlen(comando)) + 2);
		_strcat(_strcat(_strcpy(path_cmd, head_path->str), "/"), comando);
		if (stat(path_cmd, &st) == 0)
		{
			if (access(path_cmd, (R_OK | X_OK)) == 0)
				return (path_cmd);
			else if (access(path_cmd, (R_OK & X_OK)) == 0)
			{
				printError(num_cmd, 1, comando, func_name);
				free(path_cmd);
				return (NULL);
			}
		}
		free(path_cmd);
		head_path = head_path->next;
	}
	if (head_path->next == NULL)
	{
		printError(num_cmd, 0, comando, func_name);
		return (NULL);
	}
	return (NULL);
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
	int i = 0;
	char *token = NULL, *full_path = NULL, *env = NULL;

	for (i = 0; environ[i]; i++)
	{
		env = malloc(_strlen(environ[i]) + 1);
		_strcpy(env, environ[i]);
		token = strtok(env, "=");
		if ((_strcmp(token, direccion)) == 0)
		{
			token = strtok(NULL, "=");
			if (token)
			{
				full_path = malloc(_strlen(token) + 1);
				_strcpy(full_path, token);
				free(env);
				return (full_path);
			}
		}
		free(env);
		token = NULL;
	}
	return (NULL);
}

