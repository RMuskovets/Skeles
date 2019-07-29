#ifndef _KERNEL_VIDEO_TTY_H
#define _KERNEL_VIDEO_TTY_H

#include <stddef.h>
#include <stdint.h>

void set_framebuffer(uint32_t *multiboot);

void terminal_initialize(uint8_t);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#endif
