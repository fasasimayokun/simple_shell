#include "shell.h"
/**
 * is_cmd - a func that checks if a file is an executable cmd
 * @infor: the struct info
 * @pth: the file path
 * Return: 1 (true) else 0
 */
int is_cmd(infor_t *infor, char *pth)
{
	struct stat str;

	(void)infor;
	if (!pth || stat(pth, &str))
		return (0);

	if (str.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * rep_chars - a func that duplicates the char
 * @pthstr: the str path
 * @start: the starting pos
 * @stp: the stopping pos
 * Return: the addres to the new buf
 */
char *rep_chars(char *pthstr, int start, int stp)
{
	static char buff[1024];
	int nm = 0, k = 0;

	for (k = 0, nm = start; nm < stp; nm++)
		if (pthstr[nm] != ':')
			buff[k++] = pthstr[nm];
	buff[k] = 0;
	return (buff);
}
/**
 * find_pth - a func that finds the command in the path str
 * @infor: the struct info
 * @pthstr: the str path
 * @cmd: the commad to look for
 * Return: the full path of the command
 */
char *find_pth(infor_t *infor, char *pthstr, char *cmd)
{
	int nm = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((str_len(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (is_cmd(infor, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[nm] || pthstr[nm] == ':')
		{
			pth = rep_chars(pthstr, curr_pos, nm);
			if (!*pth)
			{
				str_cat(pth, cmd);
			}
			else
			{
				str_cat(pth, "/");
				str_cat(pth, cmd);
			}
			if (is_cmd(infor, pth))
				return (pth);
			if (!pthstr[nm])
				break;
			curr_pos = nm;
		}
		nm++;
	}
	return (NULL);
}
