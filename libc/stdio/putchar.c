#include <stdio.h>

#if defined(__is_libk)
// #ifndef GRAPHICS
// #include <kernel/tty.h> // text mode; just text
// #else
// #include <kernel/video-tty.h> // graphics mode; draw the text
// #endif
#include <kernel/video-tty.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
