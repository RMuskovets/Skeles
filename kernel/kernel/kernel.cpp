#define GRAPHICS

#include <stdio.h>

#include <kernel/vga.h>
#include <kernel/vesa.h>
#include <kernel/video-tty.h>
#include <kernel/mem.h>

#define SHELL_PROMPT "root@kernel$ "

extern "C" void kernel_main(uint32_t *multiboot) {
	uint32_t* memupper = (uint32_t*)(((size_t)multiboot) + 8);
	set_framebuffer(multiboot);
	terminal_initialize(VGA_COLOR_GREEN);
	new_mem_mgr(*memupper, 64*1048576);
	puts(" ________  ___  __    _______   ___       _______   ________  ________  ________      ");
	puts("|\\   ____\\|\\  \\|\\  \\ |\\  ___ \\ |\\  \\     |\\  ___ \\ |\\   ____\\|\\   __  \\|\\   ____\\     ");
	puts("\\ \\  \\___ \\ \\  \\/  /|\\ \\   __/|\\ \\  \\    \\ \\   __/|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\___|_    ");
	puts(" \\ \\_____  \\ \\   ___  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\_|/_\\ \\_____  \\ \\  \\\\\\  \\ \\_____  \\   ");
	puts("  \\|____|\\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\_|\\ \\|____|\\  \\ \\  \\\\\\  \\|____|\\  \\  ");
	puts("    ____\\_\\  \\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ \\_______\\____\\_\\  \\ ");
	puts("   |\\_________\\|__| \\|__|\\|_______|\\|_______|\\|_______|\\_________\\|_______|\\_________\\");
	puts("   \\|_________|                                       \\|_________|        \\|_________|");
	terminal_initialize(VGA_COLOR_LIGHT_GREY);
	puts("");
	puts(SHELL_PROMPT);
}

