#include "library.h"

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
	int j = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] == s2[i])
			j++;
		i++;
	}
	if (i == j && i == _strlen(s2))
		return (0);
	else
		return (-1);
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
 * @strg1: string to be copied to.
 * @strg2: string to copy from.
 * Return: the dest of the string
 */
char *_strcat(char *strg1, char *strg2)
{
	char *start = strg1;

	while (*strg1 != '\0')
		strg1++;

	while (*strg2 != '\0')
	{
		*strg1 = *strg2;
		strg1++;
		strg2++;
	}

	*strg1 = '\0';
	return (start);
}
