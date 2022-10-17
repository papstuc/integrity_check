#include "crc.h"

UNSIGNED_INT crc(UNSIGNED_INT base_hash, UNSIGNED_INT value)
{
	return CRC_INTRIN(base_hash, value);
}

UNSIGNED_INT hash_section(UNSIGNED_INT* data, UNSIGNED_INT size)
{
	UNSIGNED_INT result = 0;

	for (UNSIGNED_INT i = 0u; i < size; i++)
	{
		result = crc(result, ((unsigned char*)data)[i]);
	}

	return result;
}