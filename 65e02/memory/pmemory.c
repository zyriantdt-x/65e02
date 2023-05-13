#include "pmemory.h"

void reset_memory( Memory* memory ) {
	// clear RAM
	set_memory( memory, RAM_START, 0, MAX_RAM );

	// clear IO
	set_memory( memory, IO_START, 0, MAX_IO );
}

void set_memory( Memory* memory, word address, byte value, size_t total_bytes ) {
	while( total_bytes-- > 0 ) {
		write_address( memory, address++, value );
	}
}

void write_address( Memory* memory, word address, byte value ) {
	if( address > ROM_START ) {
		// do something here?
		return;
	}
	if( address > IO_START ) {
		memory->io[ address - IO_START ] = value;
		return;
	}
	if( address > RAM_START ) {
		memory->ram[ address - RAM_START ] = value;
		return;
	}
}