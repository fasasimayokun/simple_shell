#include "shell.h"
/**
 * my_env - a func that prints the present environment
 * @infor: the struct containing args used to maintain
 * fucntion header
 * Return: 0 (success)
 */
int my_env(infor_t *infor)
{
	print_arr_str(infor->env);
	return (0);
}

/**
 * get_env - a func that gets the val of an environ var
 * @infor: struct containing args used to maintain
 * funciton header
 * @name: the env variable name
 * Return: the val
 */
char *get_env(infor_t *infor, const char *name)
{
	list_t *nod = infor->env;
	char *pt;

	while (nod)
	{
		pt = begins_with(nod->str, name);
		if (pt && *pt)
			return (pt);
		nod = nod->next;
	}
	return (NULL);
}
/**
 * _mysetenv - a func that initialize a new env var
 * or update an existing one
 * @infor: struct containing args used to maintain
 * function header
 * Return: 0 (success)
 */
int _mysetenv(infor_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(infor, infor->argv[1], infor->argv[2]))
	{
		return (0);
	}

	return (1);
}

/**
 * _myunsetenv - a func that unset an env variable
 * @infor: struct containing args used to maintain func header
 * Return: 0 (success)
 */
int _myunsetenv(infor_t *infor)
{
	int nm;

	if (infor->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (nm = 1; nm <= infor->argc; nm++)
		_unsetenv(infor, infor->argv[nm]);
	return (0);
}

/**
 * populate_env_arr - a func that populates env linked list
 * @infor: struct conataining args used to maintain function header
 * Return: 0 (success)
 */
int populate_env_arr(infor_t *infor)
{
	list_t *nod = NULL;
	size_t nm;

	for (nm = 0; environ[nm]; nm++)
	{
		add_node_end(&nod, environ[nm], 0);
	}
	infor->env = nod;
	return (0);
}
