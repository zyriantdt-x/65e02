#pragma once
#include "processor_types.h"
#include "instructions/instructions.h"
#include "../memory/pmemory.h"

typedef struct {
	// specialist registers
	word	program_counter;
	byte	stack_pointer;
	byte	processor_status;	// carry, zero, interrupt disable, decimal mode, break command, break command, overflow, negative

	// general purpose registers
	byte	accumulator_register;
	byte	x_register;
	byte	y_register;

	// address bus/memory
	Memory address_bus;
} Processor;

void reset_processor( Processor* processor, byte rom_image[ MAX_ROM ] );

void execute_instruction( Processor* processor );