#include "shell.h"
/**
 * err_atoi - a func that converts a str to an int
 * @st: the str to convert
 * Return: converted num else 0 (no number present in the str)
 */
int err_atoi(char *st)
{
	int nm = 0;
	unsigned long int res = 0;

	if (*st == '+')
	{
		st++;
	}
	for (nm = 0; st[nm] != '\0'; nm++)
	{
		if (st[nm] >= '0' && st[nm] <= '9')
		{
			res = res * 10;
			res = res + (st[nm] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (res);
}
/**
 * print_bas - a func that prints a num in base 10
 * @num: the num
 * @fd: the fd to write to
 * Return: num of chars to print
 */
int print_bas(int num, int fd)
{
	int (*__putchar)(char) = _putchar;
	int nm, cnt = 0;
	unsigned int _abs_;
	unsigned int temp;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		_abs_ = -num;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = num;
	temp = _abs_;
	for (nm = 1000000000; nm > 1; nm /= 10)
	{
		if (_abs_ / nm)
		{
			__putchar('0' + temp / nm);
			cnt++;
		}
		temp = temp % nm;
	}
	__putchar('0' + temp);
	cnt++;

	return (cnt);
}

/**
 * print_err - a func that prints an err message
 * @infor: the param and return info structure
 * @estr: the str containing err type
 * Return: convert num else 0
 */
void print_err(infor_t *infor, char *estr)
{
	_eputs(infor->fname);
	_eputs(": ");
	print_bas(infor->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infor->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * convert_num - a func that converts a num to the base specified
 * @num: the number to convert
 * @base: the base
 * @flags: the arg flags
 * Return: a str
 */
char *convert_num(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char *ptr;
	char sgn = 0;
	unsigned long nm = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		nm = -num;
		sgn = '-';
	}
	arr = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do {
		*--ptr = arr[nm % base];
		nm = nm / base;
	} while (nm != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}
/**
 * detach_comments - a func that replaces the 1st inst of '#' with NULL
 * @buff: the str addrs to modify
 * Return: void (nothing)
 */
void detach_comments(char *buff)
{
	int nm;

	for (nm = 0; buff[nm] != '\0'; nm++)
		if (buff[nm] == '#' && (!nm || buff[nm - 1] == ' '))
		{
			buff[nm] = '\0';
			break;
		}
}
