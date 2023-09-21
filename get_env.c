#include "shell.h"
/**
 * get_environ - a func that returns the str array copy of environ
 * @infor: the struct containing args used to maintain function header
 * Return: 0 (success)
 */
char **get_environ(infor_t *infor)
{
	if (!infor->environ || infor->env_changed)
	{
		infor->environ = arr_to_strings(infor->env);
		infor->env_changed = 0;
	}
	return (infor->environ);
}

/**
 * _unsetenv - a func that unset an environment var
 * @infor: the struct containing args used to maintain function header
 * @varb: the str environment variable property
 * Return: 1 (on delete) else 0
 */
int _unsetenv(infor_t *infor, char *varb)
{
	list_t *nod = infor->env;
	size_t nm = 0;
	char *pt;

	if (!nod || !varb)
		return (0);

	while (nod)
	{
		pt = begins_with(nod->str, varb);
		if (pt && *pt == '=')
		{
			infor->env_changed = delete_node_at_pos(&(infor->env), nm);
			nm = 0;
			nod = infor->env;
			continue;
		}
		nod = nod->next;
		nm++;
	}
	return (infor->env_changed);
}

/**
 * set_env - a func that initialize a new environment var or
 * update an existing one
 * @infor: the struct containing args used to maintain function header
 * @varb: the str environment variable property
 * @val: the str environment variable value
 * Return: 0 (successe)
 */
int set_env(infor_t *infor, char *varb, char *val)
{
	char *bufr = NULL;
	list_t *nod;
	char *pt;

	if (!varb || !val)
		return (0);
	bufr = malloc(str_len(varb) + str_len(val) + 2);
	if (!bufr)
		return (1);
	str_cpy(bufr, varb);
	str_cat(bufr, "=");
	str_cat(bufr, val);
	nod = infor->env;
	while (nod)
	{
		pt = begins_with(nod->str, varb);
		if (pt && *pt == '=')
		{
			free(nod->str);
			nod->str = bufr;
			infor->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(infor->env), bufr, 0);
	free(bufr);
	infor->env_changed = 1;
	return (0);
}
