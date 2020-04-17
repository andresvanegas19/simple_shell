#include "library.h"

/**
 * verificarbuffer - checks if buffer receives bothersome characters.
 * @buffer: buffer containing what was printed by user.
 * @validar: ammount of chars in buffer.
 * @func_name: name of our function.
 * @num_cmd: number of times our func has been executed.
 *
 * Return: 0 or -1 if it fails.
 */
int verificarbuffer(char *buffer, int validar, char *func_name, int num_cmd)
{
	char losnulos[4] = {' ', '\n', '\t'};
	int i = 0, j = 0, error = 0, punto = 0, spacedot = 0;

	for (i = 0; buffer[i]; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (buffer[i] == losnulos[j])
				error++;
		}
	}
	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '.')
			punto++;
		if (buffer[i] == '.' && (buffer[i + 1] == ' ' || buffer[i + 1] == '\t'))
			spacedot++;
	}
	if ((punto >= 2 && spacedot > 0) && (error + punto) == validar)
	{
		printError2(num_cmd, func_name);
		return (-1);
	}
	if (punto == 1 && (error + punto) == validar)
		return (-1);
	if (error == validar)
		return (-1);
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
			if (stat(token[0], &st) == 0)
			{
				if (access(token[0], (R_OK | X_OK)) == 0)
				{
					command(token[0], token, environ);
					return (0);
				}
				else
					return (-1);
			}
	}
	if ((*token)[0] == '.' && (*token)[1] == '/')
	{
/* Check if the file exists and use the bitwise to check is executable*/
		if (stat(token[0], &st) == 0)
		{
			if (access(token[0], (R_OK | X_OK)) == 0)
			{
				command(token[0], token, environ);
				return (0);
			}
			else
				return (-1);
		}
	}
	return (1);
}
