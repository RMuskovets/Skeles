#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/font.h>

#include "vga.h"

uint32_t *framebuffer;
uint32_t fb_w, fb_h, fb_p, fb_bpp;

uint32_t col = 0;
uint32_t row = 0;

uint32_t max_col, max_row;

uint32_t toRGB(vga_color foreground)
{
	switch (foreground)
	{
		case 0: return 0xff000000;
		case 1: return 0xff0000ff;
		case 2: return 0xff00ff00;
		case 3: return 0xff00ffff;
		case 4: return 0xffff0000;
		case 5: return 0xffff00ff;
		case 6: return 0xff8b4513;
		case 7: return 0xffd3d3d3;
		case 8: return 0xffa9a9a9;
		case 9: return 0xff00bfff;
		case 10:return 0xff7cfc00;
		case 11:return 0xffe0ffff;
		case 12:return 0xfff08080;
		case 13:return 0xffff80ff;
		case 14:return 0xffcd8032;
		case 15:return 0xffffffff;
	}
}

void print_ch(char c)
{
	int x = (col*GLYPH_WIDTH);
	int y = (row*GLYPH_HEIGHT);

	int off = GLYPH_OFFSET(c);
	int gsz = GLYPH_HEIGHT;
	uint32_t color = toRGB(VGA_COLOR_MAGENTA);
	for (int dy = 0; dy < GLYPH_HEIGHT; dy++)
	{
		uint8_t pxrow = FONT[off+dy];
		int fp = (y+dy) * fb_p;
		for (int dx = 0; dx < GLYPH_WIDTH; dx++)
		{
			int px = pxrow >> dx & 1;
			if (px == 1)
				framebuffer[fp] = color;
			fp += fb_bpp;
		}
	}
}

void set_framebuffer(uint32_t *multiboot)
{
	framebuffer = (uint32_t *) multiboot[22];
	fb_p = multiboot[24];
	fb_w = multiboot[25];
	fb_h = multiboot[26];
	fb_bpp = multiboot[27] >> 24;

	max_col = fb_w / 8;
	max_row = fb_h / 16;
}

void terminal_initialize(void)
{

}

void terminal_putchar(char c)
{
	if (c == '\n')
	{
		col = 0;
		if (++row == max_row) {
			row = 0;
		}
	} else
	{
		print_ch(c);
		if (++col == max_col) {
			col = 0;
			if (++row == max_row) {
				row = 0;
			}
		}
	}
}

void terminal_write(const char* data, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char* data)
{
	for (int i = 0; data[i]; ++i)
		terminal_putchar(data[i]);
}
