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
#include <dirent.h>
/* estructura sobre el env*/

/**
 * struct path_of_the_directory - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list structure.
 */
typedef struct path_of_the_directory
{
	char *str;
	struct path_of_the_directory *next;

} struct_path;

int built(struct_path *head_path, char **token, char *buffer,  char *func_name,
int num_cmd);
int built2(char **token, char *func_name, int num_cmd);
int change_the_dir(char **token, char *func_name, int num_cmd);

struct_path *made_the_linked_list_path(char *path);
struct_path *add_node_end(struct_path **head, char *str);
struct_path *made_the_linked_list_enviroment(char **environ);
void free_list(struct_path *head);
int set_env(char *name_var, char *overwrite_var, char **environ);


/* Para manejar el env y errno*/
extern char **environ;

/*manejar sign y commandos */
void manejar_signal(int valor);

/* verificar que no hay errores*/
int verificarbuffer(char *buffer, int validar, char *func_name, int num_cmd);

/* Imprimir errores */
int printError(int num_cmd, int validacion, char *command,  char *func_name);

/* obtener los path y otras cosas*/
char *get_path(char **environ, char *direccion);
char *basic_commands(char *comando, struct_path *head_path, char *func_name,
		     int num_cmd);
int handlethedouble(char **token,  char *func_name, int num_cmd);
void printError2(int num_cmd,  char *func_name);

/* Funciones made by us*/
char *print_env(char **environ);
void exitfuncion(char *signal);

/* Manipular los strings */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *strg1, char *strg2);

/* funcion del commando del arg*/
int command(char *path, char **args, char **environ);

/* Funcion que ajunta el promp */
int prompt(struct_path *head_path, char *func_name, int num_cmd);
int magic(struct_path *head_path, char **token, char *buffer,  char *func_name,
int num_cmd);
int support_magic(char **token);



char *strrev(char *str);
char *pitoa(int v);


#endif /* GRANDPARENT_H */
