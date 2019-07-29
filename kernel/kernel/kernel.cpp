#define GRAPHICS

#include <stdio.h>

#include <kernel/vga.h>
#include <kernel/vesa.h>
#include <kernel/video-tty.h>
#include <kernel/mem.h>

#define SHELL_PROMPT "root@kernel$ "

void setup_terminal(uint32_t *multiboot)
{
	set_framebuffer(multiboot);
	terminal_initialize();
}


void setup_memmgr(uint32_t *multiboot)
{
	uint32_t* memupper = (uint32_t*)multiboot[2];
	new_mem_mgr(*memupper, 64*1048576);
}

extern "C" void kernel_main(uint32_t *multiboot) {
	setup_terminal(multiboot);
	setup_memmgr(multiboot);

	puts("hello, world");

	terminal_free();
}
