#pragma once
#include "../processor/processor_types.h"

#define MAX_RAM		0x4000	// 16 kb/16384 bytes
#define MAX_IO		0x4000	// 16 kb/16384 bytes
#define MAX_ROM		0x8000	// 32 kb/32768 bytes

#define RAM_START	0x0000
#define IO_START	0x4000
#define ROM_START	0x8000

typedef struct {
	byte ram[ MAX_RAM ];
	byte io[ MAX_IO ];
	byte rom[ MAX_ROM ];
} Memory;