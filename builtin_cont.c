#include "shell.h"
/**
 * my_history - a func that displays the history list one command by line
 * @infor: the struct containing args for const function header
 * Return: 0 (success)
 */
int my_history(infor_t *infor)
{
	print_arr(infor->history);
	return (0);
}

/**
 * unset_alias - a func that sets alias to str
 * @infor: the parameter struct
 * @st: the str alias
 * Return: 0 (success)
 */
int unset_alias(infor_t *infor, char *st)
{
	char *pt, ch;
	int rt;

	pt = str_chr(st, '=');
	if (!pt)
	{
		return (1);
	}
	ch = *pt;
	*pt = 0;
	rt = delete_node_at_pos(&(infor->alias), get_node_pos(infor->alias,
				node_begins_with(infor->alias, st, -1)));
	*pt = ch;
	return (rt);
}

/**
 * set_alias - a func that sets alias to str
 * @infor: param structure
 * @st: the str alias
 * Return: 0 (success)
 */
int set_alias(infor_t *infor, char *st)
{
	char *pt;

	pt = str_chr(st, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(infor, st));
	unset_alias(infor, st);
	return (add_node_end(&(infor->alias), st, 0) == NULL);
}

/**
 * print_alias - a func that prints an alias str
 * @nod: the alias node
 * Return: 0 (success)
 */
int print_alias(list_t *nod)
{
	char *pt = NULL, *nm = NULL;

	if (nod)
	{
		pt = str_chr(nod->str, '=');
		for (nm = nod->str; nm <= pt; nm++)
		_putchar(*nm);
		_putchar('\'');
		_puts(pt + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_alias - a func that mimics the alias builtin the manual alias
 * @infor: the struct args used to maintain const functions header
 * Return: 0 (success)
 */
int my_alias(infor_t *infor)
{
	int nm = 0;
	char *pt = NULL;
	list_t *nod = NULL;

	if (infor->argc == 1)
	{
		nod = infor->alias;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (nm = 1; infor->argv[nm]; nm++)
	{
		pt = str_chr(infor->argv[nm], '=');
		if (pt)
		{
			set_alias(infor, infor->argv[nm]);
		}
		else
		{
			print_alias(node_begins_with(infor->alias, infor->argv[nm], '='));
		}
	}
	return (0);
}
