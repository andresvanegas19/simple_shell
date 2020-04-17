#include "library.h"

/**
 * handlethedouble - this function is for check the : in the path
 * @token: Pointer to tokenized buffer.
 * @func_name: Info typed by user.
 * @num_cmd: number of times error has been printed.
 *
 * Return: 0 or what the chosen function returns
 */
int handlethedouble(char **token,  char *func_name, int num_cmd)
{
	char *ptr = NULL;
	struct stat st;

	ptr = get_path(environ, "PATH");
	if (ptr)
	{
		if (*ptr == ':')
		{
			if (stat(token[0], &st) == 0)
			{
				if (access(token[0], (R_OK | X_OK)) == 0)
				{
					command(token[0], token, environ);
					free(ptr);
					return (0);
				}
				else
				{
					printError(num_cmd, 1, token[0], func_name);
					free(ptr);
					return (0);
				}
			}
		}
	}
	free(ptr);
	return (-1);
}
