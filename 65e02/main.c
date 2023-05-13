#include <stdio.h>
#include <stdlib.h>
#include "processor/processor.h"
#include "util/console_utils.h"

Processor processor;

int main( int argc, char* argv[] ) {
	byte rom_image[ MAX_ROM ];

	reset_processor( &processor, rom_image );

	return EXIT_SUCCESS;
}