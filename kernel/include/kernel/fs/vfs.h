#ifndef _KERNEL_VFS
#define _KERNEL_VFS

#include <disk.h>

typedef struct file_data {
	uint8_t is_directory;
	uint16_t files_num;
	uint64_t ptr;
} __attribute__((packed)); // 12b

typedef struct file {
	uint32_t    vfs_id;
	uint64_t    file_id;
	uint64_t    parent_id;
	uint32_t    name_len;
	//char       *name;
	uint64_t    name_ptr;
	uint64_t    data_ptr;
} file_t __attribute__((packed)); // 40b 

typedef struct vfs {
	uint32_t vfs_id;
	uint16_t files_num;
	uint64_t ptr;
} vfs_t __attribute__((packed)); // 14b

vfs_t *vfs(disk_t *);
void vfs_free(vfs_t *);
file_t *vfs_newfile();

#endif