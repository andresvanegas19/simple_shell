#include "library.h"
/* gcc -Wall -Werror -Wextra -pedantic debug.c -o hsh */
/* valgrind --leak-check=full --show-leak-kinds=all hsh */

int main(int ac, char **av)
{
	char *path = NULL;
	struct_path *head = NULL;
	int validacion = 0;

	(void) av;
	if (ac > 2)
	{
		perror("Error: ");
		return (0);
	}

	path = get_path(environ);
	if (path)
		head = made_the_linked_list_path(path);

/* Si no es isatty es porque nos estan pasando una pipeta, y reconoce que nos pasaron una pipeta*/
/* aca nos retorna un numero para evaluar que no nos imprima nuestro promp */
	if (isatty(0))
		validacion = 100;

	while(1)
		prompt(head, validacion);
}

/*WOrking fine*/
/* se le pasa la linked list a la funcion*/
int magic(struct_path *head, char **token, char *buffer)
{
	int i;
	char *path_cmd = NULL, raiz[5] ="/bin/";
	struct stat st;


	for (i = 0; raiz[i] == (*token)[i] && i < 5; i++)
		if (i == 4)
		{
			if (stat(token[0], &st) == 0)
			{
			command(token[0], token, environ);
			return (0);
			}
		}

	if (head != NULL)
		path_cmd = basic_commands(token[0],head);
	if (!path_cmd)
		return(0);
	if (path_cmd)
	{
/* Verificar si el comando tiene permisos para ejecutarse*/
		if (stat(path_cmd, &st) == 0)
		{
			command(path_cmd, token, environ);
			return (0);
		}
		else
			perror(path_cmd);
		return (0);
	}

	free(path_cmd);

	if (strcmp(token[0], "exit") == 0)
	{
/* a token dos hay que transformarlo en un numero*/
		free(buffer);
		free_list(head);
		exitfuncion();
	}
	else if (strcmp(token[0], "env") == 0)
	{
		print_env(environ);
		return (0);
	}
	else if (lstat(token[0], &st) == 0)
	{
		command(token[0],token, environ);
		return(0);
	}
	return(0);
/* Aca retorna -1 si no encuentra nada de los comandos ejecutados */
}


int command(char *path, char **args, char **environ)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("sh");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(args[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else
		child_pid = wait(&status);

	return (0);
}



/* todavia no working fine*/
char *prompt(struct_path *head, int validacion)
{
	char *buffer = NULL, *divide[200];
	size_t length = 0;
	int i = 0, j = 0, validar = 0, espacioss = 0;

	if (validacion == 100)
		write(STDOUT_FILENO, "noseagay$ ", strlen("noseagay$ "));

	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);
/* Si obtengo un valor negativo de getline, mean that, se van a salir de la funcion */
	if(validar == EOF)
	{
		free_list(head);
		if (validacion == 100)
			write(1,"\n",2);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	espacioss = verificarbuffer(&buffer, validar);
	if (espacioss == -1)
	{
		free(buffer);
		return (NULL);
	}

	for (; buffer[i] != '\n'; i++)
		;
	buffer[i] = '\0';

	divide[j] = strtok(buffer, " \t");
	while (divide[j] != NULL)
		divide[++j] = strtok(NULL, " \t");

	magic(head, divide, buffer);

	free(buffer);
	return(NULL);
}

/*WOrking fine*/
/* funcion abre memoria */
char *basic_commands(char *comando, struct_path *head)
{
	struct stat st;
	char *path_cmd = NULL;

	while (head->next)
	{
		path_cmd= malloc((strlen(head->str) + strlen(comando)) + 2);
		strcat(strcat(strcpy(path_cmd, head->str), "/"), comando);
		if (stat(path_cmd, &st) == 0)
			return(path_cmd);

		free(path_cmd);
		head = head->next;
	}

	return (NULL);
}

void print_env(char **environ)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO,"\n", 2);
	}
}

void exitfuncion(void)
{
	exit(0);
}

int verificarbuffer(char **buffer, int validar)
{
	char losnulos[4] = {'\n', ' ', '\t'};
	int i = 0, j = 0, error = 0;

	for (i = 0; (*buffer)[i]; i++)
		for (j = 0; j < 4; j++)
			if ((*buffer)[i] == losnulos[j])
				error++;

	if (error == validar)
		return(-1);

	return (0);
}

/*WOrking fine*/
void manejar_signal()
{
	write(STDOUT_FILENO, "\nnoseagay$ ", strlen("\nnoseagay$ "));
}

/*WOrking fine*/
struct_path *made_the_linked_list_path(char *path)
{
	struct_path *head = NULL;
	char *token = NULL;

	token = strtok(path, ":");

	while (token)
	{
		add_node_end(&head, token);
		token = strtok(NULL, ":");
	}
	return (head);
}

/*WOrking fine*/
/* funcion abre memoria */
struct_path *add_node_end(struct_path **head, char *str)
{
	struct_path *newNode = NULL, *end = *head;

	newNode = malloc(sizeof(struct_path));
	if (newNode == NULL)
	{
		perror("Error: ");
		return (NULL);
	}

	newNode->str = strdup(str);
	newNode->next = NULL;
	if (!*head)
	{
		*head = newNode;
		return (*head);
	}
	while (end->next != NULL)
		end = end->next;
	end->next = newNode;

	return (newNode);
}

/*WOrking fine*/
void free_list(struct_path *head)
{
	struct_path *back;
	while (head)
	{
		back = head->next;
		free(head->str);
		free(head);
		head = back;
	}
}

/*WOrking fine*/
char *get_path(char **environ)
{
	int i = 0, validacion = 0;
	char *token = NULL;

	for (i = 0; environ[i]; i++)
	{
		token = strtok(environ[i], "=");
		validacion = _strcmp(token,"PATH");
		if (validacion == 0)
			return (token = strtok(NULL, "="));
		token = NULL;
	}
	perror("Error : not found the enviromental variable - path");
	return(NULL);
}

/* Working fine */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

