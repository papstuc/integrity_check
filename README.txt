integrity_check
-------------------------
hashes every writeable section at startup and makes a snapshot every 2 seconds of all of these sections again and compares them against each other.
hashing is done using a specific MSVC compiler intrinsic and can be used on both 64-bit and 32-bit: _mm_crc32_u64 for amd64 and _mm_crc32_u32 for ia-32.
the hashes are saved in a selfwritten linked list and later on properly freed from the heap.
