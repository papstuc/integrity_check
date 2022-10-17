#include "pe.h"
#include "list.h"
#include "crc.h"

uintptr_t* obtain_image_base(char* image_name)
{
	return (uintptr_t*)GetModuleHandle(image_name);
}

PIMAGE_DOS_HEADER obtain_dos_header(uintptr_t* image_base)
{
	return (((PIMAGE_DOS_HEADER)image_base)->e_magic != IMAGE_DOS_SIGNATURE) ? 0 : (PIMAGE_DOS_HEADER)image_base;
}

PIMAGE_NT_HEADERS obtain_nt_headers(uintptr_t* image_base, PIMAGE_DOS_HEADER dos_header)
{
	return ((PIMAGE_NT_HEADERS)(((uintptr_t)image_base) + dos_header->e_lfanew))->Signature != 0x4550 ? 0 : (PIMAGE_NT_HEADERS)(((uintptr_t)image_base) + dos_header->e_lfanew);
}

p_list_t obtain_sections(uintptr_t* image_base, PIMAGE_NT_HEADERS nt_headers)
{
	if (!nt_headers)
	{
		return 0;
	}

	p_list_t list = obtain_list();

	if (!list)
	{
		return 0;
	}

	PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers);

	for (WORD i = 0; i < nt_headers->FileHeader.NumberOfSections; i++, section_header++)
	{
		if (((section_header->Characteristics & IMAGE_SCN_MEM_WRITE) == 0))
		{
			section_t section = { 0 };
			strcpy_s(section.name, IMAGE_SIZEOF_SHORT_NAME, section_header->Name);

			section.virtual_address = section_header->VirtualAddress;
			section.virtual_size = section_header->Misc.VirtualSize;
			section.characteristics = section_header->Characteristics;

			uintptr_t* section_address = (uintptr_t*)((uintptr_t)image_base + section_header->VirtualAddress);

			section.crc = hash_section(section_address, section_header->Misc.VirtualSize);

			list_add(list, section);
		}
	}

	return list;
}