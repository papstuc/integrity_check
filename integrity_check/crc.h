#pragma once

#include <intrin.h>
#include <stdint.h>

#ifdef _WIN64
#define CRC_INTRIN _mm_crc32_u64
#define UNSIGNED_INT unsigned __int64
#else
#define CRC_INTRIN _mm_crc32_u32
#define UNSIGNED_INT unsigned int
#endif

UNSIGNED_INT crc(UNSIGNED_INT base_hash, UNSIGNED_INT value);
UNSIGNED_INT hash_section(UNSIGNED_INT* data, UNSIGNED_INT size);
