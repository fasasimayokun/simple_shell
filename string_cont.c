#include "shell.h"
/**
 * str_cpy - a func that copies a str from dest to source
 * @dest: the destination arr
 * @src: the source array
 * Return: addrs of the dest
 */
char *str_cpy(char *dest, char *src)
{
	int nm = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[nm])
	{
		dest[nm] = src[nm];
		nm++;
	}
	dest[nm] = 0;
	return (dest);
}
/**
 * str_dup - a func that duplicates a str
 * @st: the str to duplicate
 * Return: addrs to the duplicated str
 */
char *str_dup(const char *st)
{
	int cnt = 0;
	char *rt;

	if (st == NULL)
		return (NULL);
	while (*st++)
		cnt++;

	rt = malloc(sizeof(char) * (cnt + 1));
	if (!rt)
		return (NULL);
	for (cnt++; cnt--;)
		rt[cnt] = *--st;
	return (rt);
}

/**
 * _puts - a func that prints string input
 * @st: the string to print
 * Return: void(nothing)
 */
void _puts(char *st)
{
	int nm = 0;

	if (!st)
		return;
	while (st[nm] != '\0')
	{
		_putchar(st[nm]);
		nm++;
	}
}
/**
 * _putchar - a func that writes a char to the stdout
 * @ch: the char to output
 * Return: 1 (success)
 */
int _putchar(char ch)
{
	static int nm;
	static char bufr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || nm >= WRITE_BUF_SIZE)
	{
		write(1, bufr, nm);
		nm = 0;
	}
	if (ch != BUF_FLUSH)
		bufr[nm++] = ch;
	return (1);
}
