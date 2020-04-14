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
			if (stat(token[0], &st) == 0 && st.st_mode & S_IXUSR)
			{
				command(token[0], token, environ);
				return (0);
			}
	}
/* Checks if what is received is a ./something type executable */
	if ((*token)[0] == '.' || ((*token)[0] == '.' && (*token)[1] == '/'))
	{
/* Check if the file exists and use the bitwise to check is executable*/
		if (stat(token[0], &st) == 0 && st.st_mode & S_IXUSR)
			command(token[0], token, environ);
		else
			perror("no permissions");
		return (0);
	}
	return (-1);
}
/**
 * builtint_functions - checks possible instances for printing and executes
 * the command
 * @head_path: Pointer to head_path of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 *
 * Return: 0 or what the chosen function returns
 */
int built(struct_path *head_path, char **token, char *buffer)
{
	if (strcmp(token[0], "exit") == 0)
	{
/* a token dos hay que transformarlo en un numero*/
		free(buffer);
		free_list(head_path);
		exitfuncion(token[0]);
	}
	else if (strcmp(token[0], "env") == 0)
	{
		print_env(environ);
		return (0);
	}

	return (-1);

}

/* se deben manejar errores de permisos*/
/**
 * magic - checks possible instances for printing and executes the one
 * for each specific case (function hub).
 * @head_path: Pointer to head_path of linked list.
 * @token: Pointer to tokenized buffer.
 * @buffer: Buffer without '\n'.
 *
 * Return: 0 or what the chosen function returns
 */
int magic(struct_path *head_path, char **token, char *buffer,  char *func_name, int num_cmd)
{
	char *path_cmd = NULL, *ptr = NULL;
	struct stat st;
	int retorno = 0;

	retorno = built(head_path, token, buffer);
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
 * printError - it will print the error
 * @validacion: to choose what kind of error print
 * @num_cmd: is the counter to track how many fails it appear
 * @command: the command it has to try
 *
 */
void printError(int num_cmd, int validacion, char *command,  char *func_name)
{
	char *num_str = pitoa(num_cmd);
	/* validacion == 0 significa que no va encontrar el comando */
	if (validacion == 0)
	{
		write(1, func_name, _strlen(func_name));
		/* aca va el itoa que convierte de numero a string*/
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": command not found", 20);
		write(1, "\n", 1);
		free(num_str);
	}
	if (validacion == 1)
	{
		write(1, func_name, _strlen(func_name));
		/* aca va el itoa que convierte de numero a string*/
		write(1, ": ", 2);
		write(1, num_str, _strlen(num_str));
		write(1, ": ", 2);
		write(1, command, _strlen(command));
		write(1, ": Permission denied", 20);
		write(1, "\n", 1);
		free(num_str);
	}
}

/**
 * prompt - prints promt, checks for errors in it, tokenizes it and calls magic
 * @head_path: pointer to first element in linked list.
 * @validacion: number sent by isatty to determine whether to print or not.
 *
 * Return: NULL.
 */
char *prompt(struct_path *head_path, int validacion, char *func_name, int num_cmd)
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
 * basic_commands - opens space in memory and allocates directions of
 * basic commands.
 * @comando: command to execute.
 * @head_path: pointer to first element in singly linked list.
 *
 * Return: Null.
 */
char *basic_commands(char *comando, struct_path *head_path)
{
	struct stat st;
	char *path_cmd = NULL;

	while (head_path->next)
	{
		path_cmd = malloc((_strlen(head_path->str) + _strlen(comando)) + 2);
		_strcat(_strcat(_strcpy(path_cmd, head_path->str), "/"), comando);
		if (stat(path_cmd, &st) == 0 && st.st_mode & S_IXUSR)
			return (path_cmd);
		free(path_cmd);
		head_path = head_path->next;
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
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 2);
	}
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
	exit(0);
}

/**
 * verificarbuffer - checks if buffer receives bothersome characters.
 * @buffer: buffer containing what was printed by user.
 * @validar: ammount of chars in buffer.
 *
 * Return: 0 or -1 if it fails.
 */
int verificarbuffer(char *buffer, int validar, char *func_name, int num_cmd)
{
	char losnulos[5] = {' ', '\n', '.', '\t'};
	int i = 0, j = 0, error = 0, punto = 0;

	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '.')
			punto++;
		for (j = 0; j < 5; j++)
		{
			if (buffer[i] == losnulos[j])
				error++;
		}
	}

	if (error == validar)
	{
		i -= 1;
		buffer[i] = '\0';
		if (punto == 2)
			printError(num_cmd, 1, buffer, func_name);
		else if (punto >= 2)
			printError(num_cmd, 0, buffer, func_name);
		return (-1);
	}
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
	write(STDOUT_FILENO, "\nnoseagay$ ", _strlen("\nnoseagay$ "));
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
	struct_path *head_path = NULL;
	char *token = NULL;

	token = strtok(path, ":");
	while (token)
	{
		add_node_end(&head_path, token);
		token = strtok(NULL, ":");
	}
	return (head_path);
}

/**
 * made_the_linked_list_enviroment - creates linked list of enviromental var
 * @environ: is a double pointer to the enviromental var
 *
 * Return: head, pointer to first element of linked list.
 */
struct_path *made_the_linked_list_enviroment(char **environ)
{
	struct_path *head = NULL;
	int i;

	for (i = 0; environ[i]; i++)
/*Se le pasa la direccion de memoria para que pueda modificar head*/
		add_node_end(&head, environ[i]);

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
	newNode->str = _strdup(str);
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

int print_list(struct_path *h)
{
	int compareer;
	for (compareer = 0; h; compareer++)
	{
			printf("%s\n",h->str);
		h = h->next;
	}
	return (compareer);
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
		env = malloc(_strlen(environ[i]) + 1);
		_strcpy(env, environ[i]);
		token = strtok(env, "=");
		validacion = _strcmp(env, direccion);
		if (validacion == 0)
		{
			token = strtok(NULL, "=");
			if (token)
			{
				full_path = malloc(_strlen(token) + 1);
				_strcpy(full_path, token);
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
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * _strlen - count the characters a string have
 * @s: pointer to the variable string
 * Return: the value of i
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; ++i)
		;
	return (i);
}

/**
 * _strcpy - create an strcpy.
 * @dest: destination string.
 * @src: source to be copied.
 *
 * Return: the dest of the string
 */

char *_strcpy(char *dest, char *src)
{
	int cont;

	for (cont = 0; src[cont] != '\0'; cont++)
		dest[cont] = src[cont];

	dest[cont] = src[cont];
	return (dest);
}

/**
 * _strdup - newly space in memory, which contains a copy of the string
 * @str: pointer to the new string
 *
 * Return: an string.
 */
char *_strdup(char *str)
{
	char *nstr;
	int a = 0, b;
	if (str == NULL)
		return (NULL);
	while (str[a])
		a++;

	nstr = malloc((a + 1) * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	for (b = 0; b <= a; b++)
		nstr[b] = str[b];

	return (nstr);
}

/**
 * _strcat - concatenates two strings.
 * @dest: string to be copied to.
 * @src: string to copy from.
 * Return: the dest of the string
*/
char *_strcat(char *strg1, char *strg2)
{
	char *start = strg1;

	while(*strg1 != '\0')
		strg1++;

	while(*strg2 != '\0')
	{
		*strg1 = *strg2;
		strg1++;
		strg2++;
	}

	*strg1 = '\0';
	return (start);
}

char *pitoa(int v)
{
	char *str = malloc(2);
	char table[11] = "0123456789";
	char *p= str;
	unsigned int n = v;
	while(n>=10)
	{
		*p++=table[n%10];
		n/=10;
	}
	*p++=table[n];
	*p='\0';
	return strrev(str);
}

char *strrev(char *str)
{
	char c, *front, *back;

	for(front = str, back = str + _strlen(str) - 1; front < back; front++, back--)
	{
		c = *front;
		*front = *back;
		*back = c;
	}

	return (str);
}
