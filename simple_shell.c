#include "library.h"
/* gcc -Wall -Werror -Wextra -pedantic *.c -o hsh */
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
	struct_path *head_path = NULL;
	/*struct_path *head_env = NULL;*/
	int validacion = 0, num_cmd = 0;

/* Aca recibe el archivo, hace un loop dependiendo de las lineas de codigo*/
/* y cuando ya acabe el loop retorna si ejecutarse el demas codigo*/
	if (ac != 1)
	{
		perror("Error: Too may starting parameters.");
		return (0);
	}
	path = get_path(environ, "PATH");
	if (path)
	{
		head_path = made_the_linked_list_path(path);
		free(path);
	}

	/*head_env = made_the_linked_list_enviroment(environ);*/

	while (1)
	{
		if (isatty(0))
			validacion = 5;
		num_cmd++;
		prompt(head_path, validacion, av[0], num_cmd);
	}

	return (0);
}

/* se deben manejar errores de permisos*/
/**
 * magic - checks possible instances for printing and executes the one
 * for each specific case (function hub).
 * @head_path: Pointer to head_path of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 * @func_name: Info typed by user.
 * @num_cmd: number of times error has been printed.
 *
 * Return: 0 or what the chosen function returns
 */
int magic(struct_path *head_path, char **token, char *buffer,  char *func_name,
int num_cmd)
{
	char *path_cmd = NULL, *ptr = NULL;
	struct stat st;
	int retorno = 0;

	retorno = built(head_path, token, buffer, func_name, num_cmd);
	if (retorno == 0)
		return (0);
	retorno = 0;

	/* Checks if path variable is obstructed by :*/
	ptr = get_path(environ, "PATH");
	if (ptr)
		if (*ptr == ':')
			if (stat(token[0], &st) == 0 && st.st_mode & S_IXUSR)
			{
				command(token[0], token, environ);
				free(ptr);
				return (0);
			}
	free(ptr);
	retorno = support_magic(token);
	if (retorno == 0)
		return (0);

	if (head_path != NULL)
		path_cmd = basic_commands(token[0], head_path);
	if (!path_cmd)
	{
		printError(num_cmd, 0, token[0], func_name);
		return (0);
	}
/* Checks if command has execute permissions  whit the path_cmd*/
	if (stat(path_cmd, &st) == 0 && st.st_mode & S_IXUSR)
	{
		command(path_cmd, token, environ);
		free(path_cmd);
	}
	return (0);
}

/**
 * prompt - prints promt, checks for errors in it, tokenizes it and calls magic
 * @head_path: pointer to first element in linked list.
 * @validacion: number sent by isatty to determine whether to print or not.
 * @func_name: Info typed by user.
 * @num_cmd: number of times error has been printed.
 *
 * Return: NULL.
 */
char *prompt(struct_path *head_path, int validacion, char *func_name,
int num_cmd)
{
	char *buffer = NULL, *divide[200];
	size_t length = 0;
	int i = 0, j = 0, validar = 0, espacioss = 0;

	if (validacion == 5)
		write(STDOUT_FILENO, "ShellOfDoom$ ", strlen("ShellOfDoom$ "));
	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);
/* Checks if buffer ammount of chars is EOF */
	if (validar == EOF)
	{
		free_list(head_path);
		if (validacion == 5)
			write(1, "\n", 2);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
/* Checks for spaces or tabs in buffer*/
	espacioss = verificarbuffer(buffer, validar, func_name, num_cmd);
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
	magic(head_path, divide, buffer, func_name, num_cmd);
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
