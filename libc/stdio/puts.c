#include <stdio.h>

#ifdef __is_libk
#include <kernel/video-tty.h>
#endif

int puts(const char* string) {
	//eturn printf("%s\n", string);
	terminal_writestring(string);
}
