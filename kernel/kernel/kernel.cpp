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
	puts(" ");

	// puts(" \033[1;34m    _____   \033[1;34muser\033[1;37m@\033[1;34mcore\n");
 //    puts("\033[1;34m   / ____|  \033[1;37mOS:       \033[0;37mskift\n");
 //    puts("\033[1;34m  | (___    \033[1;37mKERNEL:   \033[0;37mhjert\n");
 //    puts("\033[1;34m   \\___ \\   \033[1;37mUPTIME:   \033[0;37m00:00\n");
 //    puts("\033[1;34m   ____)|  \033[1;37mSHELL:    \033[0;37m/bin/sh\n");
 //    puts("\033[1;34m  |_____/   \n");
 //    puts("\033[1;34m            \033[1;30;40m##\033[1;41;31m##\033[1;42;32m##\033[1;43;33m##\033[1;44;34m##\033[1;45;35m##\033[1;46;36m##\033[1;47;37m##\033[0m\n");

 //    puts("FAILLED\rSUCCESS\n");

	terminal_setcolor(VGA_COLOR_CYAN);
	puts("root");
	terminal_setcolor(VGA_COLOR_LIGHT_RED);
	puts("@");
	terminal_setcolor(VGA_COLOR_GREEN);
	puts("kernel");
	terminal_setcolor(VGA_COLOR_LIGHT_RED);
	puts("$ ");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);

	terminal_free();
}
