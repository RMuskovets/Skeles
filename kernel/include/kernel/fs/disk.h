#ifndef _KERNEL_DISK_DRV
#define _KERNEL_DISK_DRV

uint8_t disk_read(uint64_t, uint16_t);
uint8_t disk_write(uint8_t, uint64_t, uint16_t);

#endif