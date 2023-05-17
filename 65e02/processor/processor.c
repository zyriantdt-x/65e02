#include "processor.h"

void reset_processor( Processor* processor, byte rom_image[ MAX_ROM ] ) {
	// reset specialist registers
	processor->program_counter		= 0x8000;		// beginning of ROM
	processor->stack_pointer		= 0x00;			// stack begins at 0x0100 - register stores low byte
	processor->processor_status		= 0b00000000;	// clear all flags

	// reset general purpose registers
	processor->accumulator_register = 0x00;
	processor->x_register			= 0x00;
	processor->y_register			= 0x00;

	// reset memory and load ROM image
	reset_memory( &( processor->address_bus ), rom_image );

	// unhalt processor
	processor->halted				= false;

	// set clock
	processor->last_cycle			= clock();
}

void execute_instruction( Processor* processor ) {
	Instruction instruction = read_address( &( processor->address_bus ), processor->program_counter++ );
	cycle_processor( processor );

	switch( instruction ) {
		// LDA -> load accumulator
		case LDA_IMM8: {
			// get imm8 value
			byte value = read_address( &( processor->address_bus ), processor->program_counter++ );
			cycle_processor( processor );

			// load accumulator with value
			processor->accumulator_register = value;

			// if accumulator is set to zero, set zero flag
			if( value == 0x00 ) processor->processor_status = processor->processor_status | 0b01000000;

			// if bit 7 is enabled, set negative flag
			if( ( value & 0b10000000 ) > 0 ) processor->processor_status = processor->processor_status | 0b00000001;

			break;
		}
		// ADC -> add with carry
		case ADC_IMM8: {
			// get numbers to add
			byte additional_value	= read_address( &( processor->address_bus ), processor->program_counter++ );
			cycle_processor( processor );
			byte accumulator_value	= processor->accumulator_register;

			// calculator sum
			byte new_value = additional_value + accumulator_value;

			// if the new value is set to zero, set zero flag
			if( new_value == 0x00 ) processor->processor_status = processor->processor_status | 0b01000000;

			// if the new value has overflowed, set the carry flag
			if( new_value < additional_value || new_value < accumulator_value ) processor->processor_status = processor->processor_status | 0b10000000;

			// if the seventh bit is set, set the negative flag
			if( new_value & ( 1 << 6 ) ) processor->processor_status | 0b00000001;

			// load accumulator with sum
			processor->accumulator_register = new_value;

			break;
		}
		// JMP -> jump
		case JMP_IMM16: {
			// get address
			byte low_byte = read_address( &( processor->address_bus ), processor->program_counter++ );
			cycle_processor( processor );
			byte high_byte = read_address( &( processor->address_bus ), processor->program_counter++ );
			cycle_processor( processor );

			// combine bytes
			word jump_address = ( high_byte << 8 ) | low_byte;

			processor->program_counter = jump_address;
			break;
		}
		default: {
			// i want to do a memory dump here - this is technically a crash.
			processor->halted = true;
			break;
		}
	}
}

void cycle_processor( Processor* processor ) {
	while( clock() < processor->last_cycle + CLOCKS_PER_SEC ) { Sleep( 1 ); } // 1 (and a bit?) hz
	print_processor_data( processor );
	processor->last_cycle = clock();
}