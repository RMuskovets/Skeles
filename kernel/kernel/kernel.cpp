#define GRAPHICS

#include <stdio.h>

#include <kernel/vesa.h>
#include <kernel/mem.h>
#include <kernel/ui/window.h>
// #include <kernel/text.h>
// #include <kernel/video-tty.h>

#define SHELL_PROMPT "root@kernel$ "

// void setup_terminal(uint32_t *multiboot)
// {
// 	set_framebuffer(multiboot);
// 	terminal_initialize();
// }


void setup_memmgr(uint32_t *multiboot)
{
	uint32_t* memupper = (uint32_t*)multiboot[2];
	new_mem_mgr(*memupper, 64*1048576);
}

void loading_screen(window_t *desktop)
{
	desktop->draw(desktop);
	
}

extern "C" void kernel_main(uint32_t *multiboot) {
	//setup_terminal(multiboot);
	set_framebuffer(multiboot);
	setup_memmgr(multiboot);
	//puts("hello, world!");

	//terminal_free();

	window_t *desktop = window(nullptr, "", 0, 0, 1024, 768);
	desktop->border_color = 0xffffffff;
	desktop->background_color = 0xffffffff;
	desktop->draw(desktop);

	window_t *wnd = window(desktop, "", 10, 10, 128, 100);
	wnd->border_color = 0xff000000;
	wnd->background_color = 0xff00ffff;
	wnd->draw(wnd);

	// set_printing_coords(900, 10);
	// set_fg_color(0xff000000);
	// set_bg_color(0xff00ffff);
	// put_string("hello, world");

	// set_printing_coords(300, 50);
	// put_string("hi");
}
