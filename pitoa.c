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
		n/= 10;
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
