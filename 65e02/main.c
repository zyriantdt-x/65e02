#include <stdio.h>
#include <stdlib.h>
#include "processor/processor.h"
#include "util/console_utils.h"

Processor processor;

int main( int argc, char* argv[] ) {
	reset_processor( &processor );

	return EXIT_SUCCESS;
}