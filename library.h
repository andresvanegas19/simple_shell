#ifndef GRANDPARENT_H
#define GRANDPARENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

/* estructura sobre el env*/
typedef struct path_of_the_directory
{
	char *str;
	struct path_of_the_directory *next;

} struct_path;

struct_path *made_the_linked_list_path(char *path);
struct_path *add_node_end(struct_path **head, char *str);
void free_list(struct_path *head);

/* Para manejar el env*/
extern char **environ;


/*manejar sign y commandos */
void manejar_signal();
void print_promp();

/* obtener los path y otras cosas*/
char *get_path(char **environ);
char *found_made_comands(char *comando, struct_path *head);
char *found_basic_cmd(char *comando, struct_path *head);
char *found_thecommands(char *comando, struct_path *head);

/* Funciones made by us*/
void print_env();
void exitfuncion(struct_path *head);

/* Manipular los strings */
int _strcmp(char *s1, char *s2);

/* funcion del commando del arg*/
int command(char **args);

/* Funcion que ajunta el promp */
void prompt(struct_path *head);
void magic(struct_path *head, char **token);


#endif /* GRANDPARENT_H */
