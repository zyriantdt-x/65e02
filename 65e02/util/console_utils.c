#include "console_utils.h"

void console_print_at(short x, short y, char* message) {
	HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD print_coords = { x,y };
	
	SetConsoleCursorPosition( console_handle, print_coords );
	WriteConsoleA( console_handle, message, strlen( message ), NULL, NULL );
}

void console_clear() {
    // clear console
    COORD top_left = { 0, 0 };
    HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo( console_handle, &screen );
    FillConsoleOutputCharacterA(
        console_handle, ' ', screen.dwSize.X * screen.dwSize.Y, top_left, &written
    );
    FillConsoleOutputAttribute(
        console_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, top_left, &written
    );
    SetConsoleCursorPosition( console_handle, top_left );

    // hide cursor
    CONSOLE_CURSOR_INFO console_cursor_info;
    GetConsoleCursorInfo( console_handle, &console_cursor_info );
    console_cursor_info.bVisible = 0;
    SetConsoleCursorInfo( console_handle, &console_cursor_info );
}