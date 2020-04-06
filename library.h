#ifndef GRANDPARENT_H
#define GRANDPARENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* Para manejar el env*/
extern char **environ;

/* imprime el promp*/
void prompt(void);

/*manejar sign y commandos */
void manejar_signal();
void print_promp();

/* obtener los path y otras cosas*/
char *get_path(char **environ);
int strcompare(char *s1, char *s2);

/* estructura sobre el env*/

typedef struct dondeestaelpath
{

	char *path;
	char *shell;
	char *pwd;
	char *home;

} poth;



#endif /* GRANDPARENT_H */
