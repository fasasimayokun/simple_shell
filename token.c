#include "shell.h"
/**
 * strtowd - a func that splits a str into words
 * @str: the str input
 * @del: the delimeter
 * Return: address to an arr of strings
 */
char **strtowd(char *str, char *del)
{
	int nm, j, k, m, nmwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (nm = 0; str[nm] != '\0'; nm++)
		if (!is_delim(str[nm], del) && (is_delim(str[nm + 1], del) || !str[nm + 1]))
			nmwords++;

	if (nmwords == 0)
		return (NULL);
	st = malloc((1 + nmwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (nm = 0, j = 0; j < nmwords; j++)
	{
		while (is_delim(str[nm], del))
			nm++;
		k = 0;
		while (!is_delim(str[nm + k], del) && str[nm + k])
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[nm++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

/**
 * strtowd_2 - a func that splits str to words
 * @str: the str input
 * @del: the delimeter str
 * Return: address to an arr of strs
 */
char **strtowd_2(char *str, char del)
{
	int nm, j, k, m, nmwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (nm = 0; str[nm] != '\0'; nm++)
		if ((str[nm] != del && str[nm + 1] == del) ||
				(str[nm] != del && !str[nm + 1])
				|| str[nm + 1] == del)
			nmwords++;
	if (nmwords == 0)
		return (NULL);
	st = malloc((1 + nmwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (nm = 0, j = 0; j < nmwords; j++)
	{
		while (str[nm] == del && str[nm] != del)
			nm++;
		k = 0;
		while (str[nm + k] != del && str[nm + k] && str[nm + k] != del)
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[nm++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}
