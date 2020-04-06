#include "library.h"

/**
 * strcompare - return the comparetion of two strings
 * @s1: pointer to text string
 * @s2: pointer to text string
 *
 * Return: the comparetion
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/**
 * _strdup - newly space in memory, which contains a copy of the string
 * @str: pointer to the new string
 *
 * Return: an string.
 */

char *_strdup(char *str)
{
	char *pstr = NULL;
	int i = 0, j = 0;

	if (str == NULL)
		return (NULL);

	while (str[i])
		i++;

	pstr = malloc(sizeof(char) * (i + 1));

	if (pstr == NULL)
		return (NULL);

	while (str[j])
	{
		pstr[j] = str[j];
		j++;
	}

	return (pstr);
}