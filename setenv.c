#include "library.h"
/**
 * set_env - fucntion to set the enviroment variable
 * @name_var: is the name of the enviroment variable
 * @overwrite_var: is the result of the overwrite
 * @environ: is the global variable
 *
 * Return: is for sign to finish the program
 */
int set_env(char *name_var, char *overwrite_var, char **environ)
{
	int i = 0, j = 0, count = 0;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; j < _strlen(name_var) + 1; j++)
		{
			if (name_var[j] == environ[i][j])
				count++;
			if (count == _strlen(name_var))
			{
				strcpy(environ[i], name_var);
				strcat(environ[i], "=");
				strcat(environ[i], overwrite_var);
				return (0);
			}
		}
	}
	return (0);
}
