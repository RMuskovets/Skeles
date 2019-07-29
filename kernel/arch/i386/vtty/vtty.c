#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vesa.h>
#include <kernel/video-tty.h>
#include <kernel/font.h>
#include <kernel/vga.h>

#include <3rdparty/vtc.h>

const uint32_t start_x = 10;
const uint32_t start_y = 10;

uint32_t col = 0;
uint32_t row = 0;

uint32_t max_col, max_row;

uint32_t vga_color;

void print_ch(char);

void vtc_paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y)
{
	terminal_setcolor(cell->attr.fg);
	terminal_goto((uint32_t) x, (uint32_t) y);
	print_ch(cell->c);
}

void vtc_move_callback(vtconsole_t *vtc, vtcursor_t *cur)
{
	terminal_goto((uint32_t) cur->x, (uint32_t) cur->y);
}

vtconsole_t *vtc;

void terminal_setcolor(uint8_t vc)
{
	vga_color = vga_to_color(vc);
}

void terminal_goto(uint32_t c, uint32_t r)
{
	col = c;
	row = r;
}

void print_ch(char c)
{
	int x = (start_x+col*GLYPH_WIDTH);
	int y = (start_y+row*GLYPH_HEIGHT);
	uint32_t color = vga_color;
	int lx; int ly;
	uint8_t *bitmap = font8x8_basic[c % 128];
	for (lx = 0; lx < GLYPH_WIDTH; lx++) {
		for (ly = 0; ly < GLYPH_HEIGHT; ly++) {
			uint8_t row = bitmap[ly];
			if ((row >> lx) & 1)
				putpixeli(x+lx, y+ly, color);
		}
	}
}

void terminal_initialize()
{
	max_col = (start_x * 2 - get_width()) / GLYPH_WIDTH;
	max_row = (start_y * 2 - get_height())/ GLYPH_HEIGHT;
	vtc = vtconsole(max_col, max_row, vtc_paint_callback, vtc_move_callback);
}

void terminal_free()
{
	vtconsole_delete(vtc);
	vga_color = 0;
	max_col = 0;
	max_row = 0;
}

void terminal_putchar(char c)
{
	vtconsole_putchar(vtc, c);
}

void terminal_write(const char* data, size_t size)
{
	// for (int i = 0; i < size; ++i)
	// {
	// 	terminal_putchar(data[i]);
	// }
	vtconsole_write(vtc, data, size);
}

void terminal_writestring(const char* data)
{
	vtconsole_write(vtc, data, strlen(data));
}
