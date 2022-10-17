#include "list.h"

p_list_t obtain_list()
{
	p_list_t list = malloc(sizeof(struct _list_t));

	if (list != 0)
	{
		list->head = 0;
		list->size = 0;
	}

	return list;
}

void free_list(p_list_t list)
{
	if (!list)
	{
		return;
	}

	p_node_t current = list->head;

	while (current)
	{
		p_node_t node = current;
		current = current->next;
		free(node);
	}

	list->head = 0;
	list->size = 0;
	free(list);
}

void list_add(p_list_t list, section_t section)
{
	if (!list)
	{
		return;
	}

	p_node_t node = malloc(sizeof(struct _node_t));

	if (!node)
	{
		return;
	}

	node->next = 0;
	node->section = section;

	if (list->head == 0)
	{
		list->head = node;
	}
	else
	{
		p_node_t currrent = 0;
		currrent = list->head;

		while (currrent->next)
		{
			currrent = currrent->next;
		}

		currrent->next = node;
	}

	list->size++;
}