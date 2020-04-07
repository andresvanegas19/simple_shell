#include "library.h"

int main()
{
	char *path = NULL;
	struct_path *head = NULL;

	path = get_path(environ);
	head = made_the_linked_list_path(path);

	prompt(head);

//	found_cmmd("NULL", head);
//	printf("%s\n",head->str);
}
/*
char made_comands(char *comando)
{

	if (strcmp(comando, "exit") == 0)
		exitfuncion();

	return (NULL);

}*/

/* Esta funcion abre memoria */
char *found_cmmd(char *comando, struct_path *head)
{
	struct stat st;
	char *path_cmd = NULL;

	if (stat(comando, &st) == 0)
	{
//		printf("%s\n", comando);
		return(comando);
	}

	while (head->next)
	{
	/* Abre memoria para que pueda almacenar el tamano del path y del comando, son 2 por el //0 */
		path_cmd= malloc((strlen(head->str) + strlen(comando)) + 2);
		strcpy(path_cmd, head->str);
		strcat(path_cmd, "/");
		strcat(path_cmd, comando);
//		printf("%s\n", path_cmd);
		free(path_cmd);
		head = head->next;
		if (stat(path_cmd, &st) == 0)
		{
//			printf("%s\n",path_cmd);
			return(path_cmd);
		}
	}
	perror(comando);
	return (NULL);
}

/* 4. PATH
Write a function that builds a linked list of the PATH directories.
Retorna el primer nodo de la lista linkeada */
struct_path *made_the_linked_list_path(char *path)
{
	struct_path *head = NULL;
	char *token = NULL;

	token = strtok(path, ":");

	while (token)
	{
//		printf("%s\n", token);
		add_node_end(&head, token);
		token = strtok(NULL, ":");
	}
//	printf ("%s\n", path);
//	printf ("%ld\n", sizeof(struct_path));
	return (head);
}

/*Esta funcion abre memoria, se necesita una funcion para liberar este espacio de memoria*/
struct_path *add_node_end(struct_path **head, char *str)
{
	int count = 0;
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
	perror("Error : not found the envoromental variable - path");
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
void prompt(struct_path *head)
{
	char *buffer = NULL, *divide[4];
	size_t length = 32;
	int i = 0, j = 0, validar = 0;

	print_promp();
	signal(SIGINT, manejar_signal);
	validar = getline(&buffer, &length, stdin);
/* Si obtengo un valor negativo de getline, mean that, se van a salir de la funcion */
	if(validar == EOF)
	{
		free_list(head);
		write(1,"\n",2);
		free(buffer);
		exit(EOF);
	}

	for (; buffer[i] != '\n'; i++)
		;
	buffer[i] = '\0';

	divide[j] = strtok(buffer, " ");
	while (divide[j] != NULL)
		divide[++j] = strtok(NULL, " ");

	magic(head, divide);
	//printf("%i - %i", i, j);
	//printf("%s\n",divide[0]);
	free(buffer);
}

void magic(struct_path *head, char **token)
{
	char *path_cmd = NULL;
	int i = 0;
	//printf("%s\n", token[0]);
	path_cmd = found_cmmd(token[0],head);
	printf("%s\n", path_cmd);
	token[0] = path_cmd;
	command(token);
}


int command(char **args)
{
	pid_t child_pid;
	int status;

	printf("%s\n", args[0]);
	child_pid = fork();

	if (child_pid < 0)
		return (-1);
	else if (child_pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror(args[0]);
			return (-1);
		}
	}
	else
		child_pid = wait(&status);

	return (0);
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

/* Para liberar memoria de la lista linkeada*/
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
