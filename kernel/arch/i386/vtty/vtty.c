#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/video-tty.h>
#include <kernel/vga.h>
#include <kernel/text.h>

// #define __USE_VTC

#ifdef __USE_VTC
#include <3rdparty/vtc.h>
#endif

const uint32_t start_x = 10;
const uint32_t start_y = 10;

uint32_t col = 0;
uint32_t row = 0;

uint32_t max_col, max_row;

uint32_t vga_color, bg_color;

void print_ch(char);
<<<<<<< HEAD
#ifdef __USE_VTC
=======

void print_ch_at(char c, int pos_x, int pos_y);

>>>>>>> 67c01cdde17c69eb6fcac39b5e04375b64c23ac7
static char colors[] =
{
    [VTCOLOR_BLACK] = VGA_COLOR_BLACK,
    [VTCOLOR_RED] = VGA_COLOR_RED,
    [VTCOLOR_GREEN] = VGA_COLOR_GREEN,
    [VTCOLOR_YELLOW] = VGA_COLOR_BROWN,
    [VTCOLOR_BLUE] = VGA_COLOR_BLUE,
    [VTCOLOR_MAGENTA] = VGA_COLOR_MAGENTA,
    [VTCOLOR_CYAN] = VGA_COLOR_CYAN,
    [VTCOLOR_GREY] = VGA_COLOR_LIGHT_GREY,
};

static char brightcolors[] =
{
    [VTCOLOR_BLACK] = VGA_COLOR_DARK_GREY,
    [VTCOLOR_RED] = VGA_COLOR_LIGHT_RED,
    [VTCOLOR_GREEN] = VGA_COLOR_LIGHT_GREEN,
    [VTCOLOR_YELLOW] = VGA_COLOR_LIGHT_BROWN,
    [VTCOLOR_BLUE] = VGA_COLOR_LIGHT_BLUE,
    [VTCOLOR_MAGENTA] = VGA_COLOR_LIGHT_MAGENTA,
    [VTCOLOR_CYAN] = VGA_COLOR_LIGHT_CYAN,
    [VTCOLOR_GREY] = VGA_COLOR_WHITE,
};


void vtc_paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y)
{
	if (cell->attr.bright)
	{
		terminal_setcolor(brightcolors[cell->attr.fg]);
	} else
	{
		terminal_setcolor(colors[cell->attr.fg]);
	}

	terminal_setbgcolor(colors[cell->attr.bg]);
<<<<<<< HEAD

	set_printing_coords(start_x + x, start_y + y);
	put_char(cell->c);
=======
	print_ch_at(cell->c, x, y);
>>>>>>> 67c01cdde17c69eb6fcac39b5e04375b64c23ac7
}

void vtc_move_callback(vtconsole_t *vtc, vtcursor_t *cur)
{
	terminal_goto((uint32_t) cur->x, (uint32_t) cur->y);
}

vtconsole_t *vtc;
#endif

void terminal_setcolor(uint8_t vc)
{
	set_fg_color(vga_to_color(vc));
}
void terminal_setbgcolor(uint8_t vc)
{
	set_bg_color(vga_to_color(vc));
}

void terminal_goto(uint32_t c, uint32_t r)
{
	set_printing_coords(start_x + c*GLYPH_WIDTH, start_y + r*GLYPH_HEIGHT);
}

void print_ch_at(char c, int pos_x, int pos_y)
{
	int x = (start_x+pos_x*GLYPH_WIDTH);
	int y = (start_y+pos_y*GLYPH_HEIGHT);
	int lx; int ly;
	uint8_t *bitmap = font8x8_basic[c % 128];
	for (lx = 0; lx < GLYPH_WIDTH; lx++) {
		for (ly = 0; ly < GLYPH_HEIGHT; ly++) {
			uint8_t row = bitmap[ly];
			if ((row >> lx) & 1)
				putpixeli(x+lx, y+ly, vga_color);
			else
				putpixeli(x+lx,y+ly, bg_color);
		}
	}
}

void terminal_initialize()
{
	set_printing_coords(start_x, start_y);
	max_col = (start_x * 2 - get_width()) / GLYPH_WIDTH;
	max_row = (start_y * 2 - get_height())/ GLYPH_HEIGHT;
#ifdef __USE_VTC
	vtc = vtconsole(max_col, max_row, vtc_paint_callback, vtc_move_callback);
#endif
}

void terminal_free()
{
#ifdef __USE_VTC
	vtconsole_delete(vtc);
#endif
	vga_color = 0;
	max_col = 0;
	max_row = 0;
}

void terminal_putchar(char c)
{
#ifdef __USE_VTC
	vtconsole_putchar(vtc, c);
#else
	put_char(c);
#endif
}

void terminal_write(const char* data, size_t size)
{
#ifdef __USE_VTC
	vtconsole_write(vtc, data, size);
#else
	for (int i = 0; i < size; ++i)
	{
		terminal_putchar(data[i]);
	}
#endif
}

void terminal_writestring(const char* data)
{
	// vtconsole_write(vtc, data, strlen(data));
	terminal_write(data, strlen(data));
}
