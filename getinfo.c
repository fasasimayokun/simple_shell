#include "shell.h"
/**
 * clr_infor - a func that initializes info_t structure
 * @infor: the structure addrs
 * Return: void(nothing)
 */
void clr_infor(infor_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}

/**
 * set_infor - a func that initializes info_t structure
 * @infor: the structure addrs
 * @av: the arg vector
 * Return: void(nothing)
 */
void set_infor(infor_t *infor, char **av)
{
	int nm = 0;

	infor->fname = av[0];
	if (infor->arg)
	{
		infor->argv = strtowd(infor->arg, " \t");
		if (!infor->argv)
		{
			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = str_dup(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (nm = 0; infor->argv && infor->argv[nm]; nm++)
			;
		infor->argc = nm;

		update_alias(infor);
		update_vars(infor);
	}
}

/**
 * free_infor - a func that frees info_t structure propeties
 * @infor: the structure addrs
 * @all: true
 * Return: void(nothing)
 */
void free_infor(infor_t *infor, int all)
{
	ffrree(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (all)
	{
		if (!infor->cmd_buf)
		{
			free(infor->arg);
		}
		if (infor->env)
			free_arr(&(infor->env));
		if (infor->history)
		{
			free_arr(&(infor->history));
		}
		if (infor->alias)
		{
			free_arr(&(infor->alias));
		}
		ffrree(infor->environ);
		infor->environ = NULL;
		bffree((void **)infor->cmd_buf);
		if (infor->readfd > 2)
		{
			close(infor->readfd);
		}
		_putchar(BUF_FLUSH);
	}
}
