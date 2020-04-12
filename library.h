#ifndef GRANDPARENT_H
#define GRANDPARENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <limits.h>

/**
 * struct path_of_the_directory - singly linked list for PATH
 * @str: malloc'ed node for the list.
 * @next: link to point to the next node.
 * Description: Singly linked list to store the PATH for command navigation.
 */

typedef struct path_of_the_directory
{
	char *str;
	struct path_of_the_directory *next;
} struct_path;

struct_path *made_the_linked_list_path(char *path);
struct_path *add_node_end(struct_path **head, char *str);
void free_list(struct_path *head);

/*Helps handle env printing*/
extern char **environ;

/*Handles signal supression ctrl - c*/
void manejar_signal(int);

/*Checks buffer for errors*/
int verificarbuffer(char *buffer, int validar);

/*Prints errors*/
void print_error(int digito, char *error, char *command);

/*These handle the path, finds commands and handles their execution*/

char *get_path(char **environ, char *direccion);
char *found_made_comands(char *comando, struct_path *head);
char *basic_commands(char *comando, struct_path *head);
char *found_thecommands(char *comando, struct_path *head);

/* Functions created by us for specific functionalities*/
void print_env(char **environ);
void exitfuncion(void);

/* Compares strings */
int _strcmp(char *s1, char *s2);

/* Checks and executes commands */
int command(char *path, char **args, char **environ);

/* Handles prompt, strtok and buffer errors */
char *prompt(struct_path *head, int validacion);

/* Where magic happens. Checks buffer, handles command calling and execution */
int magic(struct_path *head, char **token, char *buffer);

#endif /* GRANDPARENT_H */
