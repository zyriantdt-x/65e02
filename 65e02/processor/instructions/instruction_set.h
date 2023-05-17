#pragma once
typedef enum {
	// LDA -> load accumulator
	LDA_IMM8	= 0xA9, // value(imm8)

	// ADC -> add with carry
	ADC_IMM8	= 0x69,	// summand(imm8)

	// JMP -> jump
	JMP_IMM16	= 0x4C,	// address(imm16)

	// STA -> store accumulator
	STA_IMM16	= 0x8D	// address(imm16)
} Instruction;