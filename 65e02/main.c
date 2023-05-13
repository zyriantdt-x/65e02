#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "processor/processor.h"
#include "util/console_utils.h"
#include "util/debug_utils.h"

Processor processor;

int main( int argc, char* argv[] ) {
	// clear the console
	console_clear();

	// check user has passed a rom image
	if( argc < 2 ) {
		printf( "Usage: 65e02.exe <rom_image.bin>" );
		return EXIT_SUCCESS;
	}

	// create rom image buffer
	byte rom_image[ MAX_ROM ];

	char* file_name = argv[ 1 ];

	// create file handle
	FILE* image_handle;
	image_handle = fopen( file_name, "rb" );

	// check if file handle is null
	if( image_handle == NULL ) {
		printf( "Unable to load ROM image" );
		return EXIT_SUCCESS;
	}

	// check binary is 32 kb
	fseek( image_handle, 0, SEEK_END );			// seek to end of file
	long image_size = ftell( image_handle );	// get current file pointer
	fseek( image_handle, 0, SEEK_SET );			// seek to beginning of file
	if( image_size > 32768 ) {
		printf( "Binary image must be 32kb" );
		return EXIT_SUCCESS;
	}

	// load image into buffer
	fread( rom_image, MAX_ROM, 1, image_handle );

	// start processor
	reset_processor( &processor, rom_image );

	int i = 3;
	while( i-- > 0 ) {
		execute_instruction( &processor );
		print_processor_data( &processor );
	}

	return EXIT_SUCCESS;
}