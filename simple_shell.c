#include "library.h"

int main()
{
	char *path = NULL;

	poth *puntero;
	prompt();
	path = get_path(environ);
	printf("%s\n", path);
}
char *get_path(char **environ)
{
	int i = 0, validacion;
	char *token = NULL;

	for (i = 0; environ[i]; i++)
	{
		token = strtok(environ[i], "=");
		validacion = strcmp(token,"PATH");
		if (validacion == 0)
			return (token = strtok(NULL, "="));

		token = NULL;
	}
	return(NULL);
}
// hacer el bucle
// que compile con los flags
// con valgrind
// que guarde el path
// y que busque la funcion

// recibir comando, recibir la variable global

// la variable global se busca el PATH

// ya tenemos PATH y comando
// se busca el comando por el PATH
void prompt(void)
{
	char *buffer = NULL, *divide[4];
	size_t length = 32;
	int i = 0, j = 0, validar = 0;
	int status;

	print_promp();
	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);

	for (; buffer[i] != '\n'; i++)
		;

	buffer[i] = '\0';

	divide[j] = strtok(buffer, " ");

	while (divide[j] != NULL)
		divide[++j] = strtok(NULL, " ");

	//printf("%i - %i", i, j);
	//printf("%s\n",divide[0]);
	free(buffer);
}

/* Para que cuando ejecute el comando ^C lo pase y siga su proceso*/
void manejar_signal()
{
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}

void print_promp(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}