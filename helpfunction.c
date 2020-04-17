#include "library.h"

/**
 * printHelp - it will choose what command is for print the instructions
 * @token: Pointer to tokenized buffer.
 *
 * Return: 0 or what the chosen function returns
 */
int printHelp(char **token)
{
	if (token[1] == NULL)
	{
		printbasic();
		return (0);
	}
	if (_strcmp(token[1], "cd") == 0)
	{
		printcd();
		return (0);
	}
	if (_strcmp(token[1], "exit") == 0)
	{
		printexit();
		return (0);
	}
	if (_strcmp(token[1], "env") == 0)
	{
		printenv();
		return (0);
	}
	write(1, "\033[0;31m", 8);
	write(1, "./hsh: help: no help topics match   ", 37);
	write(1, token[1], _strlen(token[1]));
	write(1, "    try to type help to see how many command it should reed\n", 61);
	write(1, "\033[0m", 5);
	return (0);
}

/**
 * printbasic - print the instructions of what it needs for print
 *
 */
void printbasic(void)
{
	write(1, "\033[0;33m", 8);
	write(1, "HSH, version 1.0 release in ubuntu Ubuntu 14.04 LTS\n", 52);
	write(1, "If you want to see how use a command type 'help {name}'\n", 56);
	write(1, "\n\n", 3);
	write(1, "			", 4);
	write(1, "cd [direcotry]\n", 16);
	write(1, "			", 4);
	write(1, "exit [stat]\n", 13);
	write(1, "			", 4);
	write(1, "env\n", 5);
	write(1, "\033[0m", 5);
}

/**
 * printcd - print the instructions of the command cd
 *
 */
void printcd(void)
{
	write(1, "\033[0;33m", 8);
	write(1, "cd [direcotry]\n", 16);
	write(1, "			", 4);
	write(1, "Change the current directory, and the process to do this\n", 58);
	write(1, "			", 4);
	write(1, "is that the changes the environment varibales and if no\n", 57);
	write(1, "			", 4);
	write(1, "directory is found and displays an error or if the file\n", 56);
	write(1, "			", 4);
	write(1, "is not found, display the error\n", 33);
	write(1, "\033[0m", 5);
}

/**
 * printexit - print the instructions of exit and how to use it
 *
 */
void printexit(void)
{
	write(1, "\033[0;33m", 8);
	write(1, "exit [stat]\n", 13);
	write(1, "			", 4);
	write(1, "Exit the program with a status of stat, this is a integer.\n", 60);
	write(1, "			", 4);
	write(1, "If stat is omitted,the exit status is that of the \n", 52);
	write(1, "			", 4);
	write(1, "last command executed\n", 23);
	write(1, "\033[0m", 5);
}

/**
 * printenv - print the instructions of what is the limitionts of env
 *
 */
void printenv(void)
{
	write(1, "\033[0;33m", 8);
	write(1, "env\n", 5);
	write(1, "			", 4);
	write(1, "prints all environment variables and the result changes\n", 57);
	write(1, "			", 4);
	write(1, "depending on the commands that are executed later,\n", 52);
	write(1, "			", 4);
	write(1, "there is no error if  no environment variable is found,\n", 57);
	write(1, "			", 4);
	write(1, "no more than one argument is received\n", 39);
	write(1, "\033[0m", 5);
}
