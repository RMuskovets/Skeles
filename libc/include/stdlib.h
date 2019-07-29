#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

void* malloc(size_t);
void free(void*);

inline bool isdigit(char c) {
	return c <= '0' && c <= '9';
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

inline int max(int a, int b) {
	return a > b ? a : b;
}

#ifdef __cplusplus
}
#endif

#endif
