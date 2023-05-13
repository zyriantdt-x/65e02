#include "pmemory.h"

void reset_memory( Memory* memory, byte rom_image[ MAX_ROM ] ) {
	// clear RAM
	set_memory( memory, RAM_START, 0, MAX_RAM );

	// clear IO
	set_memory( memory, IO_START, 0, MAX_IO );

	// load ROM image
	load_rom( memory, rom_image );
}

void set_memory( Memory* memory, word address, byte value, size_t total_bytes ) {
	while( total_bytes-- > 0 ) {
		write_address( memory, address++, value );
	}
}

void write_address( Memory* memory, word address, byte value ) {
	if( address >= ROM_START ) {
		if( memory->rom_write_protected ) {
			// do something here?
		} else {
			memory->rom[ address - ROM_START ] = value;
		}
		return;
	}
	if( address >= IO_START ) {
		memory->io[ address - IO_START ] = value;
		return;
	}
	if( address >= RAM_START ) {
		memory->ram[ address - RAM_START ] = value;
		return;
	}
}

void load_rom( Memory* memory, byte rom_image[ MAX_ROM ] ) {
	memory->rom_write_protected = false;

	size_t total_bytes = MAX_ROM;
	word address = 0x0000;
	while( total_bytes-- > 0 ) {
		write_address( memory, address + ROM_START, rom_image[ address++ ] );
	}

	memory->rom_write_protected = true;
}

byte read_address( Memory* memory, word address ) {
	if( address >= ROM_START )
		return memory->rom[ address - ROM_START ];
	if( address >= IO_START )
		return memory->io[ address - IO_START ];
	if( address >= RAM_START )
		return memory->ram[ address - RAM_START ];
}