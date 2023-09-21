#include "shell.h"
/**
 * _eputs - a func that prints a str input
 * @st: the str to print
 * Return: void (nothing)
 */
void _eputs(char *st)
{
	int nm = 0;

	if (!st)
	{
		return;
	}
	while (st[nm] != '\0')
	{
		_eputchar(st[nm]);
		nm++;
	}
}
/**
 * _eputchar - a func that writes a char to stderr
 * @ch: the char to print
 * Return: 1 (success)
 */
int _eputchar(char ch)
{
	static int nm;
	static char bufr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || nm >= WRITE_BUF_SIZE)
	{
		write(2, bufr, nm);
		nm = 0;
	}
	if (ch != BUF_FLUSH)
	{
		bufr[nm++] = ch;
	}
	return (1);
}

/**
 * put_fd - a func that writes the char to the given fd
 * @ch: the char to print
 * @fd: the fd to write to
 * Return: 1 (success)
 */
int put_fd(char ch, int fd)
{
	static int nm;
	static char bufr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || nm >= WRITE_BUF_SIZE)
	{
		write(fd, bufr, nm);
		nm = 0;
	}
	if (ch != BUF_FLUSH)
	{
		bufr[nm++] = ch;
	}
	return (1);
}
/**
 * _putsfd - a func that prints a str input
 * @st: the str to print
 * @fd: the fd to write to
 * Return: the num of chars to put
 */
int _putsfd(char *st, int fd)
{
	int nm = 0;

	if (!st)
	{
		return (0);
	}
	while (*st)
	{
		nm = nm + put_fd(*st++, fd);
	}
	return (0);
}
