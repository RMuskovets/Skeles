#define GRAPHICS // the graphics mode is enabled.

#include <stdio.h>

// #ifndef GRAPHICS
// #include <kernel/tty.h>
// #else
// #include <kernel/video-tty.h>
// #endif

#include <kernel/video-tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
}
