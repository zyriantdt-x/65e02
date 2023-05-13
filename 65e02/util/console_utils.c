#include "console_utils.h"

void console_print_at(short x, short y, const char* message) {
	HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD print_coords = { x,y };
	
	SetConsoleCursorPosition( console_handle, print_coords );
	WriteConsoleA( console_handle, message, strlen( message ), NULL, NULL );
}