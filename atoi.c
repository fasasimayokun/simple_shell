#include "shell.h"

/**
 * _atoi - a func that converts a str to an int
 * @st: the str to convert
 * Return: 0 if no nums were present in str else convert num
 */
int _atoi(char *st)
{
	int nm, flag = 0, res;
	int sgn = 1;
	unsigned int result = 0;

	for (nm = 0; st[nm] != '\0' && flag != 2; nm++)
	{
		if (st[nm] == '-')
			sgn = sgn * -1;

		if (st[nm] >= '0' && st[nm] <= '9')
		{
			flag = 1;
			result = result * 10;
			result = result + (st[nm] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sgn == -1)
	{
		res = -result;
	}
	else
	{
		res = result;
	}

	return (res);
}

/**
 * interactive_mod - a func that returns true if shell is in interactiv mode
 * @infor: structure addr
 * Return: 1 for interactive mode else 0
 */
int interactive_mod(infor_t *infor)
{
	return (isatty(STDIN_FILENO) && infor->readfd <= 2);
}

/**
 * is_delim - a func that checks if char is a delimeter
 * @ch: the character to check
 * @del: the delimeter str
 * Return: 1 if the char is a delimeter else 0
 */
int is_delim(char ch, char *del)
{
	while (*del)
	{
		if (*del++ == ch)
		{
			return (1);
		}
	}
	return (0);
}
/**
 * bffree - a func that frees a ptr and initialize it with NULL
 * @pt: addrs of the ptr to free
 * Return: 1 (success) else 0
 */
int bffree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
