#include "debug_utils.h"

void print_processor_data( Processor* processor ) {
	// print program counter register
	char program_counter_string[ 16 ];
	snprintf( program_counter_string, 16, "PC = %X", processor->program_counter );
	console_print_at( 0, 0, program_counter_string );

	// print stack pointer register
	char stack_pointer_string[ 16 ];
	snprintf( stack_pointer_string, 16, "SP = %X", processor->stack_pointer );
	console_print_at( 0, 1, stack_pointer_string );

	// print status flags register
	char status_flags_string[ 16 ];
	snprintf( status_flags_string, 16, "PS = cba"/*, /*processor->processor_status*/);
	console_print_at( 0, 2, status_flags_string );

	// print accumulator register
	char accumulator_string[ 16 ];
	snprintf( accumulator_string, 16, "A = %X", processor->accumulator_register );
	console_print_at( 0, 3, accumulator_string );

	// should i free everything? /shrug
}