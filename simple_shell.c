#include "library.h"
/* gcc -Wall -Werror -Wextra -pedantic *.c -o hsh */
/* valgrind --leak-check=full --show-leak-kinds=all hsh */

/**
 * main - Checks arguments started wit the function and checks there are
 * no pipelines sent.
 * @ac: argument counter.
 * @av: argument vector. Used to print error.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *path = NULL;
	struct_path *head_path = NULL;
	int num_cmd = 0;

/* Aca recibe el archivo, hace un loop dependiendo de las lineas de codigo*/
/* y cuando ya acabe el loop retorna si ejecutarse el demas codigo*/
	if (ac != 1)
	{
		perror("Error: Too many starting parameters.");
		return (0);
	}

	path = get_path(environ, "PATH");

	if (path)
	{
		head_path = made_the_linked_list_path(path);
		free(path);
	}

	while ((1 * 1) == 1)
	{
		num_cmd++;
		prompt(head_path, av[0], num_cmd);
	}

	return (545);
}

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
	char *path_cmd = NULL;
	struct stat st;
	int retorno = 0;

	retorno = built(head_path, token, buffer, func_name, num_cmd);
	if (retorno == 0)
		return (100);

	retorno = handlethedouble(token, func_name, num_cmd);
	if (retorno == 0)
		return (100);

	retorno = support_magic(token);
	if (retorno == 0)
		return (100);
	if (head_path != NULL)
		path_cmd = basic_commands(token[0], head_path, func_name, num_cmd);

	if (!path_cmd)
		return (100);

	if (path_cmd)
	{
		if (stat(path_cmd, &st) == 0)
		{
			if (access(path_cmd, R_OK) == 0)
				if (access(path_cmd, X_OK) == 0)
				{
					command(path_cmd, token, environ);
					free(path_cmd);
				}
		}
		else
			printError(num_cmd, 1, token[0], func_name);
	}
	return (100);
}

/**
 * prompt - prints promt, checks for errors in it, tokenizes it and calls magic
 * @head_path: pointer to first element in linked list.
 * @func_name: Info typed by user.
 * @num_cmd: number of times error has been printed.
 *
 * Return: NULL.
 */
int prompt(struct_path *head_path, char *func_name, int num_cmd)
{
	char *buffer = NULL, *divide[64];
	size_t length = 0;
	int i = 0, j = 0, validar = 0, espacioss = 0;

	if (isatty(0))
		write(STDOUT_FILENO, "ShellOfDoom$ ", strlen("ShellOfDoom$ "));
	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);
/* Checks if buffer ammount of chars is EOF */
	if (validar == EOF)
	{
		free_list(head_path);
		if (isatty(0))
			write(1, "\n", 2);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
/* Checks for spaces or tabs in buffer*/
	espacioss = verificarbuffer(buffer, validar, func_name, num_cmd);
	if (espacioss == -1)
	{
		free(buffer);
		return (100);
	}

	for (; buffer[i] != '\n'; i++)
		;
	buffer[i] = '\0';

	divide[j] = strtok(buffer, " \t");
	while (divide[j] != NULL)
		divide[++j] = strtok(NULL, " \t");
	magic(head_path, divide, buffer, func_name, num_cmd);
	free(buffer);
	return (100);
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
	return (100);
}
