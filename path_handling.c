#include "library.h"

/**
 * basic_commands - opens space in memory and allocates directions of
 * basic commands.
 * @comando: command to execute.
 * @head_path: pointer to first element in singly linked list.
 * @func_name: name of function.
 * @num_cmd: times prompt has been executed.
 *
 * Return: Null.
 */
char *basic_commands(char *comando, struct_path *head_path, char *func_name,
		     int num_cmd)
{
	struct stat st;
	char *path_cmd = NULL;

	while (head_path->next)
	{
		path_cmd = malloc((_strlen(head_path->str) + _strlen(comando)) + 2);
		_strcat(_strcat(_strcpy(path_cmd, head_path->str), "/"), comando);
		if (stat(path_cmd, &st) == 0)
		{
			if (access(path_cmd, (R_OK | X_OK)) == 0)
				return (path_cmd);
			else if (access(path_cmd, (R_OK & X_OK)) == 0)
			{
				printError(num_cmd, 1,
					   comando, func_name);
				free(path_cmd);
				return (NULL);
			}
		}
		free(path_cmd);
		head_path = head_path->next;
	}
	return (NULL);
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

/**
 * print_list - prints list for path.
 * @h: list to print.
 *
 * Return: segments of list to print.
 */
int print_list(struct_path *h)
{
	int compareer;

	for (compareer = 0; h; compareer++)
	{
		printf("%s\n", h->str);
		h = h->next;
	}
	return (compareer);
}
