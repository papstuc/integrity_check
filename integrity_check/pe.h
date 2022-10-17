#pragma once

#include <Windows.h>

typedef struct _list_t list_t, * p_list_t;

typedef struct _section_t
{
	unsigned char name[IMAGE_SIZEOF_SHORT_NAME];
	DWORD virtual_address;
	DWORD virtual_size;
	DWORD characteristics;
	uintptr_t crc;
} section_t, * p_section_t;

uintptr_t* obtain_image_base(char* image_name);
PIMAGE_DOS_HEADER obtain_dos_header(uintptr_t* image_base);
PIMAGE_NT_HEADERS obtain_nt_headers(uintptr_t* image_base, PIMAGE_DOS_HEADER dos_header);
p_list_t obtain_sections(uintptr_t* image_base, PIMAGE_NT_HEADERS nt_headers);