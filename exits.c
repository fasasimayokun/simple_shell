#include "shell.h"
/**
 * _strncpy - a func that copies a n number of str
 * @dest: the destination to copy to
 * @src: the destination to copyt from
 * @num: the n num of chars to copy
 * Return: the concat str
 */
char *_strncpy(char *dest, char *src, int num)
{
	int nm, i;
	char *st = dest;

	nm = 0;
	while (src[nm] != '\0' && nm < num - 1)
	{
		dest[nm] = src[nm];
		nm++;
	}
	if (nm < num)
	{
		i = nm;
		while (i < num)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (st);
}
/**
 * _strncat - a func that concat n number of strs from one str to another
 * @dest: the 1st str
 * @src: the 2nd str
 * @num: the number of str to concatenate
 * Return: the str concatenated
 */
char *_strncat(char *dest, char *src, int num)
{
	int nm, j;
	char *st = dest;

	nm = 0;
	j = 0;
	while (dest[nm] != '\0')
	{
		nm++;
	}
	while (src[j] != '\0' && j < num)
	{
		dest[nm] = src[j];
		nm++;
		j++;
	}
	if (j < num)
		dest[nm] = '\0';
	return (st);
}
/**
 * str_chr - a func that locates a char in a str
 * @st: the string to search through
 * @ch: the char to find
 * Return: a ptr to str
 */
char *str_chr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
