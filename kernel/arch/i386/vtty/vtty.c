#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vesa.h>
#include <kernel/video-tty.h>
#include <kernel/font.h>

#include "../vga.h"

const uint32_t start_x = 10;
const uint32_t start_y = 10;

uint32_t col = 0;
uint32_t row = 0;

uint32_t max_col, max_row;

void print_ch(char c)
{
	int x = (start_x+col*GLYPH_WIDTH);
	int y = (start_y+row*GLYPH_HEIGHT);
	uint32_t color = vga_to_color(VGA_COLOR_MAGENTA);
	int lx; int ly;
	for (lx = 0; lx < 8; lx++) {
		for (ly = 0; ly < 8; ly++) {
			uint8_t row = FONT[GLYPH_OFFSET(c) + ly];
			if (row >> lx & 1)
				putpixeli(x+lx, y+ly, color);
		}
	}
}

void terminal_initialize(void)
{
	max_col = (start_x * 2 - get_width()) / GLYPH_WIDTH;
	max_row = (start_y * 2 - get_height())/ GLYPH_HEIGHT;
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
