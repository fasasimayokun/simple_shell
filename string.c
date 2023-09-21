#include "shell.h"
/**
 * str_len - a func that returns the length of a str
 * @st: the str to check
 * Return: the int length of str
 */
int str_len(char *st)
{
	int nm = 0;

	if (!st)
		return (0);

	while (*st++)
	{
		nm++;
	}
	return (nm);
}
/**
 * str_cmp - a func that performs lexicographica comparison btw 2 strs
 * @st_1: the first string input
 * @st_2: the second string input
 * Return: 0(equal) else (-1) else(1)
 */
int str_cmp(char *st_1, char *st_2)
{

	while (*st_1 && st_2)
	{
		if (*st_1 != *st_2)
		{
			return (*st_1 - *st_2);
		}
		st_1++;
		st_2++;
	}
	if (*st_1 == *st_2)
	{
		return (0);
	}
	else
	{
		return (*st_1 < *st_2 ? -1 : 1);
	}
}
/**
 * begins_with - a func that checks if a str that with the inputted str
 * @haystack: the str to search
 * @needle: the substr to look for
 * Return: addrs of the next char in haystack
 */
char *begins_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * str_cat - a func that joins two strs together
 * @dest: the destination string
 * @src: the source string
 * Return: pointer to the destination string
 */
char *str_cat(char *dest, char *src)
{
	char *nm = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (nm);
}
