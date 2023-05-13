#pragma once
typedef enum {
	LDA_IMM8	= 0xA9, // load accumulator, imm8
	ADC_IMM8	= 0x69	// add with carry, imm8
} Instruction;