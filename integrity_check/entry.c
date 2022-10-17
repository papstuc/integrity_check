#include <stdio.h>

#include "pe.h"
#include "list.h"

int main(int argc, char** argv)
{
	uintptr_t* image_base = obtain_image_base(0);

	if (!image_base)
	{
		printf("couldn't find the image base\n");
		return -1;
	}

	PIMAGE_DOS_HEADER dos_header = obtain_dos_header(image_base);
	
	if (!dos_header)
	{
		printf("couldn't find the dos header for specified the module\n");
		return -1;
	}

	PIMAGE_NT_HEADERS nt_headers = obtain_nt_headers(image_base, dos_header);

	if (!nt_headers)
	{
		printf("couldn't find the nt headers for the specified module\n");
		return -1;
	}

	p_list_t initial_sections = obtain_sections(image_base, nt_headers);

	if (!initial_sections || initial_sections->size == 0 || !initial_sections->head)
	{
		printf("couldn't obtain sections for the specified module\n");
		return -1;
	}

	p_node_t initial_node = initial_sections->head;

	while (initial_node)
	{
		printf("section name: %s\tcrc: %zu\n", initial_node->section.name, initial_node->section.crc);

		initial_node = initial_node->next;
	}

	initial_node = 0;

	unsigned int sections_okay = 1;

	while (sections_okay)
	{
		initial_node = initial_sections->head;

		p_list_t sections = obtain_sections(image_base, nt_headers);
		p_node_t sections_node = sections->head;

		while (sections_node && initial_node)
		{
			if (sections_node->section.crc != initial_node->section.crc)
			{
				printf("the %s section was modified!\n", initial_node->section.name);
				sections_okay = 0;
			}

			initial_node = initial_node->next;
			sections_node = sections_node->next;
		}

		initial_node = 0;
		sections_node = 0;

		free_list(sections);

		Sleep(2000);
	}

	free_list(initial_sections);
}