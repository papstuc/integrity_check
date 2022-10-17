#pragma once

#include "pe.h"

typedef struct _node_t
{
	section_t section;
	struct _node_t* next;
} node_t, * p_node_t;

typedef struct _list_t
{
	p_node_t head;
	size_t size;
} list_t, * p_list_t;

p_list_t obtain_list();
void free_list(p_list_t list);

void list_add(p_list_t list, section_t section);