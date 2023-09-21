#include "shell.h"
/**
 * add_node - a func that adds a node to the beginning
 * of the list
 * @head: addrs of ptr to head node
 * @st: the string fieled of the node
 * @nm: the node position used by hist
 * Return: the length of the list
 */
list_t *add_node(list_t **head, const char *st, int nm)
{
	list_t *nw_head;

	if (!head)
	{
		return (NULL);
	}
	nw_head = malloc(sizeof(list_t));
	if (!nw_head)
		return (NULL);
	mem_set((void *)nw_head, 0, sizeof(list_t));
	nw_head->num = nm;
	if (st)
	{
		nw_head->str = str_dup(st);
		if (!nw_head->str)
		{
			free(nw_head);
			return (NULL);
		}
	}
	nw_head->next = *head;
	*head = nw_head;
	return (nw_head);
}
/**
 * add_node_end - a func that adds a node to the end of the list
 * @head: the addrs of ptr to the head node
 * @st: the string field of the node list
 * @nm: the node position used by the hist
 * Return: the len of the list
 */
list_t *add_node_end(list_t **head, const char *st, int nm)
{
	list_t *nw_nod, *nod;

	if (!head)
		return (NULL);

	nod = *head;
	nw_nod = malloc(sizeof(list_t));
	if (!nw_nod)
		return (NULL);
	mem_set((void *)nw_nod, 0, sizeof(list_t));
	nw_nod->num = nm;
	if (st)
	{
		nw_nod->str = str_dup(st);
		if (!nw_nod->str)
		{
			free(nw_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = nw_nod;
	}
	else
	{
		*head = nw_nod;
	}
	return (nw_nod);
}

/**
 * print_arr_str - a func that prints only string elem of
 * a list_t linked list
 * @hd: the ptr to the 1st node
 * Return: the size of the list
 */
size_t print_arr_str(const list_t *hd)
{
	size_t nm = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil}");
		_puts("\n");
		hd = hd->next;
		nm++;
	}
	return (nm);
}

/**
 * delete_node_at_pos - a func that removes a node at the given index
 * @head: the addrs of the ptr to the 1st node
 * @pos: the position of node to delete
 * Return: 1 (success) else 0
 */
int delete_node_at_pos(list_t **head, unsigned int pos)
{
	list_t *nod;
	list_t *prev_nod;
	unsigned int nm = 0;

	if (!head || !*head)
		return (0);

	if (!pos)
	{
		nod = *head;
		*head = (*head)->next;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *head;
	while (nod)
	{
		if (nm == pos)
		{
			prev_nod->next = nod->next;
			free(nod->str);
			free(nod);
			return (1);
		}
		nm++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_arr - a func that frees all the nodes in the list
 * @head_pt: addrs of ptr of the head of the node
 * Return: void(nothing)
 */
void free_arr(list_t **head_pt)
{
	list_t *nod, *next_nod, *head;

	if (!head_pt || !*head_pt)
		return;
	head = *head_pt;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*head_pt = NULL;
}
