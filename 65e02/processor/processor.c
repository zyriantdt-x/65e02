#include "processor.h"

void reset_processor( Processor* processor, byte rom_image[ MAX_ROM ] ) {
	// reset specialist registers
	processor->program_counter = 0x8000;		// beginning of ROM
	processor->stack_pointer = 0x00;			// stack begins at 0x0100 - register stores low byte
	processor->processor_status = 0b00000000;	// clear all flags

	// reset general purpose registers
	processor->accumulator_register = 0x00;
	processor->x_register = 0x00;
	processor->y_register = 0x00;

	// reset memory and load ROM image
	reset_memory( &( processor->address_bus ), rom_image );
}

void execute_instruction( Processor* processor ) {
	Instruction instruction = read_address( &( processor->address_bus ), processor->program_counter++ );

	switch( instruction ) {
		case LDA_IM: {
			byte value = read_address( processor, &( processor->address_bus ), processor->program_counter++ );

			processor->accumulator_register = value;

			// if accumulator is set to zero, set zero flag
			if( value == 0x00 ) processor->processor_status = processor->processor_status | 0b01000000;

			// if bit 7 is enabled, set negative flag
			if( ( value & 0b10000000 ) > 0 ) processor->processor_status = processor->processor_status | 0b00000001;

			break;
		}
		default: {
			break;
		}
	}
}