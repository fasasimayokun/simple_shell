#include "shell.h"
/**
 * list_cnt - a func that determines the len of the linked list
 * @p: the ptr to the 1st node
 * Return: the size of the node list
 */
size_t list_cnt(const list_t *p)
{
	size_t nm = 0;

	while (p)
	{
		p = p->next;
		nm++;
	}
	return (nm);
}
/**
 * arr_to_strings - a func that returns an arr of strs
 * @hd: the ptr to the 1st node
 * Return: arr of strs
 */
char **arr_to_strings(list_t *hd)
{
	list_t *nod = hd;
	size_t nm = list_cnt(hd), j;
	char **strs;
	char *str;

	if (!hd || !nm)
		return (NULL);
	strs = malloc(sizeof(char *) * (nm + 1));
	if (!strs)
		return (NULL);
	for (nm = 0; nod; nod = nod->next, nm++)
	{
		str = malloc(str_len(nod->str) + 1);
		if (!str)
		{
			for (j = 0; j < nm; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = str_cpy(str, nod->str);
		strs[nm] = str;
	}
	strs[nm] = NULL;
	return (strs);
}
/**
 * print_arr - a func that prints all elems of the list_t linked list
 * @hd: the ptr to the 1st node
 * Return: the size of the linked list
 */
size_t print_arr(const list_t *hd)
{
	size_t nm = 0;

	while (hd)
	{
		_puts(convert_num(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		nm++;
	}
	return (nm);
}

/**
 * node_begins_with - a func that returns a node whose str strats with prefix
 * @nod: the ptr to the head of the list
 * @prefix: the sttr to match
 * @ch: the next char after the prefix to match
 * Return: the match node
 */
list_t *node_begins_with(list_t *nod, char *prefix, char ch)
{
	char *pt = NULL;

	while (nod)
	{
		pt = begins_with(nod->str, prefix);
		if (pt && ((ch == -1) || (*pt == ch)))
		{
			return (nod);
		}
		nod = nod->next;
	}
	return (NULL);
}

/**
 * get_node_pos - a func the gets the position of the node
 * @headd: the ptr to the head of the list
 * @nod: the ptr to the node
 * Return: the position of the node else (-1)
 */
ssize_t get_node_pos(list_t *headd, list_t *nod)
{
	size_t nm = 0;

	while (headd)
	{
		if (headd == nod)
		{
			return (nm);
		}
		headd = headd->next;
		nm++;
	}
	return (-1);
}
