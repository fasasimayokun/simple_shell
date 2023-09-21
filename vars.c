#include "shell.h"
/**
 * is_chain - a func that test if present char in buffer is a chain delim
 * @infor: the param structure
 * @bufr: the char buf
 * @pos: address of the present positon in buf
 * Return: 1
 */
int is_chain(infor_t *infor, char *bufr, size_t *pos)
{
	size_t nm = *pos;

	if (bufr[nm] == '|' && bufr[nm + 1] == '|')
	{
		bufr[nm] = 0;
		nm++;
		infor->cmd_buf_type = CMD_OR;
	}
	else if (bufr[nm] == '&' && bufr[nm + 1] == '&')
	{
		bufr[nm] = 0;
		nm++;
		infor->cmd_buf_type = CMD_AND;
	}
	else if (bufr[nm] == ';')
	{
		bufr[nm] = 0;
		infor->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = nm;
	return (1);
}

/**
 * check_chain - a func that checks if chaininig should continue
 * @infor: the param structure
 * @bufr: the char buf
 * @pt: addrs of present position in buffer
 * @id: the starting pos in buffer
 * @cnt: the buffer length
 * Return: void(nothing)
 */
void check_chain(infor_t *infor, char *bufr, size_t *pt, size_t id, size_t cnt)
{
	size_t nm = *pt;

	if (infor->cmd_buf_type == CMD_AND)
	{
		if (infor->status)
		{
			bufr[id] = 0;
			nm = cnt;
		}
	}
	if (infor->cmd_buf_type == CMD_OR)
	{
		if (!infor->status)
		{
			bufr[id] = 0;
			nm = cnt;
		}
	}
	*pt = nm;
}

/**
 * update_alias - a func that replaces an alias in a tokenized str
 * @infor: the param structure
 * Return: 1
 */
int update_alias(infor_t *infor)
{
	int nm;
	list_t *nod;
	char *ptr;

	for (nm = 0; nm < 10; nm++)
	{
		nod = node_begins_with(infor->alias, infor->argv[0], '=');
		if (!nod)
		{
			return (0);
		}
		free(infor->argv[0]);
		ptr = str_chr(nod->str, '=');
		if (!ptr)
			return (0);
		ptr = str_dup(ptr + 1);
		if (!ptr)
		{
			return (0);
		}
		infor->argv[0] = ptr;
	}
	return (1);
}
/**
 * update_vars - a func that replaces var in the tokenized str
 * @infor: the param structure
 * Return: 1
 */
int update_vars(infor_t *infor)
{
	int nm = 0;
	list_t *nod;

	for (nm = 0; infor->argv[nm]; nm++)
	{
		if (infor->argv[nm][0] != '$' || !infor->argv[nm][1])
		{
			continue;
		}
		if (!str_cmp(infor->argv[nm], "$?"))
		{
			update_string(&(infor->argv[nm]),
					str_dup(convert_num(infor->status, 10, 0)));
			continue;
		}
		if (!str_cmp(infor->argv[nm], "$$"))
		{
			update_string(&(infor->argv[nm]),
					str_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		nod = node_begins_with(infor->env, &infor->argv[nm][1], '=');
		if (nod)
		{
			update_string(&(infor->argv[nm]),
					str_dup(str_chr(nod->str, '=') + 1));
			continue;
		}
		update_string(&infor->argv[nm], str_dup(""));
	}
	return (0);
}
/**
 * update_string - a func that replaces str
 * @ol: addrs of the old arr of str
 * @nw: the new str
 * Return: 1
 */
int update_string(char **ol, char *nw)
{
	free(*ol);
	*ol = nw;
	return (1);
}
