#ifndef _KERNEL_DISK_DRV
#define _KERNEL_DISK_DRV

typedef struct disk {

} disk_t;

disk_t *disk();
void disk_free(disk_t *);
uint8_t disk_read(disk_t *, uint64_t, uint16_t);
void disk_write(disk_t *, uint64_t, uint16_t, uint8_t);


#endif