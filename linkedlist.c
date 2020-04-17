#include "library.h"

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
