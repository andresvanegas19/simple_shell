#include "library.h"

/**
 * pitoa - makes an int into a string.
 * @v: int to convert
 *
 * Return: whatever strrev delivers.
 */
char *pitoa(int v)
{
	char *str = malloc(100);
	char table[11] = "0123456789";
	char *p = str;
	unsigned int n = v;

	while (n >= 10)
	{
		*p++ = table[n % 10];
		n /= 10;
	}
	*p++ = table[n];
	*p = '\0';
	return (strrev(str));
}

/**
 * strrev - makes an int into a string.
 * @str: string to reverse.
 *
 * Return: the reversed string.
 */
char *strrev(char *str)
{
	char c, *front, *back;

	for (front = str, back = str + _strlen(str) - 1; front < back; front++,
			back--)
	{
		c = *front;
		*front = *back;
		*back = c;
	}

	return (str);
}

/**
 * isallchars - verificated is the number has a letter
 * @token: string to containt numbers or lettlers
 *
 * Return: 0 found a letter, 1 not found a letter
 */
int isallchars(char *token)
{
	int i = 0, j = 0;

	for (; token[i] != '\0'; i++)
		if ((token[i] >= 'a' && token[i] <= 'z') ||
			(token[i] >= 'A' && token[i] <= 'Z'))
			j++;

	if (j > 0)
/* found a letter into the string*/
		return (0);
	else
		return (1);
}
