#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdint.h>
#include <stddef.h>

static void* buffer_alloc(size_t bytes);
static void buffer_free(char* p_free);
void nk_malloc_init(void);
void* nk_malloc(size_t size);
void nk_free(void* p_free);
void* malloc_aligned(size_t align, size_t size);
void free_aligned(void* p_free);

int buffer_alloc_free_test(void);
int nk_malloc_free_test(void);
int malloc_aligned_test(void);
#endif

