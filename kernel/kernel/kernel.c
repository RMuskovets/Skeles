#define GRAPHICS

#include <stdio.h>

#include <kernel/vesa.h>
#include <kernel/video-tty.h>

void kernel_main(uint32_t *multiboot) {
	set_framebuffer(multiboot);
	terminal_initialize();
	puts("Hi!");
}
