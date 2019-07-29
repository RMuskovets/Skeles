#include <kernel/descriptor_tables/idt.h>

extern void idt_flush(uint32_t);

void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
