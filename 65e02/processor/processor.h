#pragma once
#include <Windows.h>
#include <time.h>
#include "processor_types.h"
#include "instructions/instructions.h"
#include "../memory/pmemory.h"

#define INSTRUCTION 0
#define ADDRESS_READ_WRITE 1

typedef struct {
	bool		halted;

	// clock
	clock_t		last_cycle;

	// specialist registers
	word		program_counter;
	byte		stack_pointer;
	byte		processor_status;	// carry, zero, interrupt disable, decimal mode, break command, break command, overflow, negative

	// general purpose registers
	byte		accumulator_register;
	byte		x_register;
	byte		y_register;

	// address bus/memory
	Memory address_bus;
} Processor;

void reset_processor( Processor* processor, byte rom_image[ MAX_ROM ] );

void execute_instruction( Processor* processor );

void cycle_processor( Processor* processor );