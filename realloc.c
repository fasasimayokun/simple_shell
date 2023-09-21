#include "shell.h"
/**
 * mem_set - a func that fills memory with a byte
 * @st: the ptr to the memory position
 * @byt: the byte to fill the mem position with
 * @num: the number of byte to fill
 * Return: a ptr to the mem area
 */
char *mem_set(char *st, char byt, unsigned int num)
{
	unsigned int nm;

	for (nm = 0; nm < num; nm++)
		st[nm] = byt;
	return (st);
}

/**
 * ffrree - a func that frees a str of strs
 * @pptr: the str of strs
 * Return: void (nothing)
 */
void ffrree(char **pptr)
{
	char **x = pptr;

	if (!pptr)
	{
		return;
	}
	while (*pptr)
	{
		free(*pptr++);
	}
	free(x);
}
/**
 * re_alloc - a func that reallocates a blok of mem
 * @ptr: ptr to the prev allocated block
 * @ol_sz: the byte size of the prev mem space
 * @nw_sz: the byte size of the new mem space
 * Return: the ptr to the old mem space
 */
void *re_alloc(void *ptr, unsigned int ol_sz, unsigned int nw_sz)
{
	char *pt;

	if (!ptr)
		return (malloc(nw_sz));
	if (!nw_sz)
	{
		return (free(ptr), NULL);
	}
	if (nw_sz == ol_sz)
		return (ptr);

	pt = malloc(nw_sz);
	if (!pt)
		return (NULL);

	ol_sz = ol_sz < nw_sz ? ol_sz : nw_sz;
	while (ol_sz--)
	{
		pt[ol_sz] = ((char *)ptr)[ol_sz];
	}
	free(ptr);
	return (pt);
}
