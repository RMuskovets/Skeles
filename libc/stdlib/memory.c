#include <stdlib.h>
#if defined(__is_libk)
#include <kernel/mem.h>
#endif

void* malloc(size_t sz) {
#if defined(__is_libk)
	return kalloc(sz);
#else
	return 0;
#endif
}

void free(void* ptr) {
#if defined(__is_libk)
	kfree(ptr);
#endif
}
