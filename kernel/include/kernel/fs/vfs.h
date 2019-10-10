#ifndef _KERNEL_VFS
#define _KERNEL_VFS

#include <disk.h>

typedef struct file {
	uint32_t    vfs_id;
	uint64_t    file_id;
	uint64_t    parent_id;
	uint32_t    name_len;
	char       *name;
	uint64_t    content_ptr;
} file_t;

typedef struct vfs {
	//disk_t *d;
	
	uint32_t vfs_id;
} vfs_t;

vfs_t *vfs(disk_t *);
void vfs_free(vfs_t *);
file_t *vfs_newfile();

#endif