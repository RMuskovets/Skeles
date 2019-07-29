#ifndef _KERNEL_MEM_H
#define _KERNEL_MEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct mem_chunk
{
	struct mem_chunk *prev;
	struct mem_chunk *next;
	bool allocated;
	size_t size;
} mem_chunk_t;

typedef struct mem_mgr
{
	mem_chunk_t *first;
} mem_mgr_t;

struct mem_mgr *new_mem_mgr();

struct mem_mgr *get_active_mem_mgr();
void *alloc(size_t);
void free(void*);

#endif