#include "shell.h"
/**
 * read_bufr - a func that reads a buf
 * @infor: the param structure
 * @bufr: the buffer
 * @sz: size
 * Return: rd
 */
ssize_t read_bufr(infor_t *infor, char *bufr, size_t *sz)
{
	ssize_t rd = 0;

	if (*sz)
	{
		return (0);
	}
	rd = read(infor->readfd, bufr, READ_BUF_SIZE);
	if (rd >= 0)
		*sz = rd;
	return (rd);
}
/**
 * get_line - a func that gets the next line of input frm STDIN
 * @infor: the param structure
 * @ptr: addrs of ptr to buffer
 * @len: size of the preallocated ptr
 * Return: int
 */
int get_line(infor_t *infor, char **ptr, size_t *len)
{
	static char bufr[READ_BUF_SIZE];
	static size_t nm, ln;
	size_t k;
	ssize_t r = 0, st = 0;
	char *pt = NULL, *new_pt = NULL, *ch;

	pt = *ptr;
	if (pt && len)
		st = *len;
	if (nm == ln)
		nm = ln = 0;

	r = read_bufr(infor, bufr, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);

	ch = str_chr(bufr + nm, '\n');
	k = ch ? 1 + (unsigned int)(ch - bufr) : ln;
	new_pt = re_alloc(pt, st, st ? st + k : k + 1);
	if (!new_pt)
		return (pt ? free(pt), -1 : -1);
	if (st)
		_strncat(new_pt, bufr + nm, k - nm);
	else
		_strncpy(new_pt, bufr + nm, k - nm + 1);

	st = st + k - nm;
	nm = k;
	pt = new_pt;

	if (len)
		*len = st;
	*ptr = pt;
	return (st);
}

/**
 * sigint_handler - a func tha block control c
 * @sig_num: the sig num
 * Return: void (nothing)
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}

/**
 * input_bufr - a func that buffers chained cmds
 * @infor: the param structure
 * @bufr: the addrs of buf
 * @len: the addrs of len variable
 * Return: the bytes read
 */
ssize_t input_bufr(infor_t *infor, char **bufr, size_t *len)
{
	ssize_t rd = 0;
	size_t len_pt = 0;

	if (!*len)
	{
		free(*bufr);
		*bufr = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		rd = getline(bufr, &len_pt, stdin);
#else
		rd = get_line(infor, bufr, &len_pt);
#endif
		if (rd > 0)
		{
			if ((*bufr)[rd - 1] == '\n')
			{
				(*bufr)[rd - 1] = '\0';
				rd--;
			}
			infor->linecount_flag = 1;
			detach_comments(*bufr);
			build_hist_arr(infor, *bufr, infor->histcount++);
			{
				*len = rd;
				infor->cmd_buf = bufr;
			}
		}
	}
	return (rd);
}
/**
 * get_num - a func that gets a line minus the newline
 * @infor: the param structure
 * Return: the bytes read
 */
ssize_t get_num(infor_t *infor)
{
	static char *bufr;
	static size_t nm, len, j;
	ssize_t rd = 0;
	char **buf_pt = &(infor->arg), *pt;

	_putchar(BUF_FLUSH);
	rd = input_bufr(infor, &bufr, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		j = nm;
		pt = bufr + nm;

		check_chain(infor, bufr, &j, nm, len);
		while (j < len)
		{
			if (is_chain(infor, bufr, &j))
				break;
			j++;
		}
		nm = j + 1;
		if (nm >= len)
		{
			nm = len = 0;
			infor->cmd_buf_type = CMD_NORM;
		}
		*buf_pt = pt;
		return (str_len(pt));
	}

	*buf_pt = bufr;
	return (rd);
}
