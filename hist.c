#include "shell.h"
/**
 * get_hist_file - a func that gets the file history
 * @infor: the param structure
 * Return: the string containing the history file
 */
char *get_hist_file(infor_t *infor)
{
	char *buff, *dr;

	dr = get_env(infor, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(dr) + str_len(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, dr);
	str_cat(buff, "/");
	str_cat(buff, HIST_FILE);
	return (buff);
}
/**
 * write_hist - a func that creates a file history
 * or adds to the existing one
 * @infor: the param structure
 * Return: 1 (success) else -1
 */
int write_hist(infor_t *infor)
{
	ssize_t fd;
	char *filename = get_hist_file(infor);
	list_t *nd = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nd = infor->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * build_hist_arr - a func that adds entry to a history linked list
 * @infor: the structure containing args used to maintain
 * function header
 * @buff: the buffer
 * @linecnt: the history linecount
 * Return: 0 (success)
 */
int build_hist_arr(infor_t *infor, char *buff, int linecnt)
{
	list_t *nd = NULL;

	if (infor->history)
	{
		nd = infor->history;
	}
	add_node_end(&nd, buff, linecnt);
	if (!infor->history)
	{
		infor->history = nd;
	}
	return (0);
}
/**
 * read_hist - a func that reads the hist from a file
 * @infor: the param structure
 * Return: the histcount (success) else 0
 */
int read_hist(infor_t *infor)
{
	int nm, last = 0, linecnt = 0;
	ssize_t fd, rdcnt, fsize = 0;
	struct stat str;
	char *buff = NULL, *fname = get_hist_file(infor);

	if (!fname)
		return (0);
	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &str))
		fsize = str.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdcnt = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdcnt <= 0)
		return (free(buff), 0);
	close(fd);
	for (nm = 0; nm < fsize; nm++)
		if (buff[nm] == '\n')
		{
			buff[nm] = 0;
			build_hist_arr(infor, buff + last, linecnt++);
			last = nm + 1;
		}
	if (last != nm)
		build_hist_arr(infor, buff + last, linecnt++);
	free(buff);
	infor->histcount = linecnt;
	while (infor->histcount-- >= HIST_MAX)
		delete_node_at_pos(&(infor->history), 0);
	renumber_hist(infor);
	return (infor->histcount);
}
/**
 * renumber_hist - a func that renumbers the hist linked
 * list after changes
 * @infor: the struct containing args used to maintain function header
 * Return: the modified histcount
 */
int renumber_hist(infor_t *infor)
{
	list_t *nod = infor->history;
	int nm = 0;

	while (nod)
	{
		nod->num = nm++;
		nod = nod->next;
	}
	return (infor->histcount = nm);
}
