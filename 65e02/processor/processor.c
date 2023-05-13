#include "processor.h"

void reset_processor( Processor* processor ) {
	// reset specialist registers
	processor->program_counter	= 0x8000;		// beginning of ROM
	processor->stack_pointer	= 0x00;			// stack begins at 0x0100 - register stores low byte
	processor->processor_status = 0b00000000;	// clear all flags

	// reset general purpose registers
	processor->accumulator_register = 0x00;
	processor->x_register			= 0x00;
	processor->y_register			= 0x00;
}