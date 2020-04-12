#include "library.h"
/* gcc -Wall -Werror -Wextra -pedantic debug.c -o hsh */
/* valgrind --leak-check=full --show-leak-kinds=all hsh */

/**
 * main - Checks arguments started wit the function and checks there are
 * no pipelines sent.
 * @ac: argument counter.
 * @av: argument vector (not used, voided at start).
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *path = NULL;
	struct_path *head = NULL;
	int validacion = 0;
	(void) av;
	if (ac != 1)
	{
		perror("Error: Too may starting parameters.");
		return (0);
	}
	path = get_path(environ, "PATH");
	if (path)
	{
		head = made_the_linked_list_path(path);
		free(path);
	}
	if (isatty(0))
		validacion = 5;
	while (1)
		prompt(head, validacion);

	return (0);
}

/**
 * magic - checks possible instances for printing and executes the one
 * for each specific case (function hub).
 * @head: Pointer to head of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 *
 * Return: 0 or what the chosen function returns
 */
int magic(struct_path *head, char **token, char *buffer)
{
	int i;
	char raiz[5] = "/bin/", *path_cmd = NULL;
	struct stat st;
	char *ptr;
/* Checks if path variable is obstructed by :*/
	ptr = get_path(environ, "PATH");
	if (ptr)
		if (*ptr == ':')
			if (stat(token[0], &st) == 0)
			{
				command(token[0], token, environ);
				free(ptr);
				return (0);
			}
	free(ptr);
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
/* If there is a /bin/something, it executes it */
	for (i = 0; raiz[i] == (*token)[i] && i < 5; i++)
		if (i == 4)
			if (stat(token[0], &st) == 0)
			{
				command(token[0], token, environ);
				return (0);
			}
/* Checks if what is received is a ./something type executable */
	if ((*token)[0] == '.' && (*token)[1] == '/')
		if (stat(token[0], &st) == 0)
		{
			command(token[0], token, environ);
			return (0);
		}
	if (head != NULL)
		path_cmd = basic_commands(token[0], head);
	if (!path_cmd)
		return (0);
/* Checks if command has execute permissions */
	if (path_cmd)
	{
		if (stat(path_cmd, &st) == 0)
		{
			command(path_cmd, token, environ);
			free(path_cmd);
			return (0);
		}
		else
			perror(path_cmd);
			free(path_cmd);
		return (0);
	}
	return (0);
/* Aca retorna -1 si no encuentra nada de los comandos ejecutados */
}

/**
 * prompt - prints promt, checks for errors in it, tokenizes it and calls magic.
 * @head: pointer to first element in linked list.
 * @validacion: number sent by isatty to determine whether to print or not.
 *
 * Return: NULL.
 */
char *prompt(struct_path *head, int validacion)
{
	char *buffer = NULL, *divide[200];
	size_t length = 0;
	int i = 0, j = 0, validar = 0, espacioss = 0;

	if (validacion == 5)
		write(STDOUT_FILENO, "noseagay$ ", strlen("noseagay$ "));
	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);
/* Checks if buffer ammount of chars is EOF */
	if (validar == EOF)
	{
		free_list(head);
		if (validacion == 5)
			write(1, "\n", 2);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
/* Checks for spaces or tabs in buffer*/
	espacioss = verificarbuffer(buffer, validar);
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
	return (NULL);
}

/**
 * command - forks and executes command.
 * @path: direction in PATH where command is located.
 * @args: Arguments for command, if any.
 * @environ: Environment for execve to find command.
 *
 * Return: 0 or -1 if fork fails.
 */
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

/**
 * basic_commands - opens space in memory and allocates directions of
 * basic commands.
 * @comando: command to execute.
 * @head: pointer to first element in singly linked list.
 *
 * Return: Null.
 */
char *basic_commands(char *comando, struct_path *head)
{
	struct stat st;
	char *path_cmd = NULL;

	while (head->next)
	{
		path_cmd = malloc((strlen(head->str) + strlen(comando)) + 2);
		strcat(strcat(strcpy(path_cmd, head->str), "/"), comando);
		if (stat(path_cmd, &st) == 0)
			return (path_cmd);

		free(path_cmd);
		head = head->next;
	}
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
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 2);
	}
}

/**
 * exitfuncion - exits.
 *
 * Return: void.
 */
void exitfuncion(void)
{
	exit(0);
}

/**
 * verificarbuffer - checks if buffer receives bothersome characters.
 * @buffer: buffer containing what was printed by user.
 * @validar: ammount of chars in buffer.
 *
 * Return: 0 or -1 if it fails.
 */
int verificarbuffer(char *buffer, int validar)
{
	char losnulos[4] = {'\n', ' ', '\t'};
	int i = 0, j = 0, error = 0;

	for (i = 0; buffer[i]; i++)
		for (j = 0; j < 4; j++)
			if (buffer[i] == losnulos[j])
				error++;
	if (error == validar)
		return (-1);
	return (0);
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
	write(STDOUT_FILENO, "\nnoseagay$ ", strlen("\nnoseagay$ "));
}

/**
 * made_the_linked_list_path - creates linked list
 * made of PATH adresses.
 * @path: path to compartmentalize.
 *
 * Return: head, pointer to first element of linked list.
 */
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

/**
 * add_node_end - adds as many nodes as needed to store PATH.
 * @head: first element of linked list.
 * @str: an adress in path.
 *
 * Return: new node.
 */
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

/**
 * free_list - frees the list containing the PATH.
 * @head: pointer to first element in linked list.
 *
 * Return: void.
 */
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
		env = malloc(strlen(environ[i]) + 1);
		strcpy(env, environ[i]);
		token = strtok(env, "=");
		validacion = strcmp(env, direccion);
		if (validacion == 0)
		{
			token = strtok(NULL, "=");
			if (token)
			{
				full_path = malloc(strlen(token) + 1);
				strcpy(full_path, token);
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
 * _strcmp - function to compare two strings.
 * @s1: string one, to compare with s2
 * @s2: string two.
 *
 * Return: comparison of both strings or 0.
 */
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
