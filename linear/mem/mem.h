#ifndef _MEM_H_
#define _MEM_H_

#include <stddef.h>

void* nk_memcpy(void* dst0, const void* src0, size_t length);
int nk_memcmp(const void* vl, const void* vr, size_t n);
void* nk_memmove(void* s1, const void* s2, size_t n);
void* nk_memset(void* dst, int c,  size_t n);
int mem_test(void);

#endif
