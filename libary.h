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
/* estructura sobre el env*/
typedef struct path_of_the_directory
{
	char *str;
	struct path_of_the_directory *next;

} struct_path;

struct_path *made_the_linked_list_path(char *path);
struct_path *add_node_end(struct_path **head, char *str);
void free_list(struct_path *head);

/* Para manejar el env y errno*/
extern char **environ;

/*manejar sign y commandos */
void manejar_signal();

/* verificar que no hay errores*/
int verificarbuffer(char **buffer, int validar);

/* Imprimir errores */
void print_error(int digito, char *error, char *command);

/* obtener los path y otras cosas*/
char *get_path(char **environ);
char *found_made_comands(char *comando, struct_path *head);
char *basic_commands(char *comando, struct_path *head);
char *found_thecommands(char *comando, struct_path *head);


/* Funciones made by us*/
void print_env(char **environ);
void exitfuncion();

/* Manipular los strings */
int _strcmp(char *s1, char *s2);

/* funcion del commando del arg*/
int command(char *path, char **args, char **environ);

/* Funcion que ajunta el promp */
char *prompt(struct_path *head, int validacion);
int magic(struct_path *head, char **token, char *buffer);

#endif /* GRANDPARENT_H */
