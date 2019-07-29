#define GRAPHICS

#include <stdio.h>

#include <kernel/vga.h>
#include <kernel/vesa.h>
#include <kernel/video-tty.h>
#include <kernel/mem.h>

#define SHELL_PROMPT "root@kernel$ "

void kernel_main(uint32_t *multiboot) {
	uint32_t* memupper = (uint32_t*)(((size_t)multiboot) + 8);
	set_framebuffer(multiboot);
	terminal_initialize(VGA_COLOR_LIGHT_GREY);
	new_mem_mgr(memupper, 64*1048576);
	puts("root@kernel$ ");
}

