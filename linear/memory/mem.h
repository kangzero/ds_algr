#ifndef _MEM_H_
#define _MEM_H_

#include <stdint.h>
#include <stddef.h>

static void* buffer_alloc(size_t bytes);
static void buffer_free(char* p_free);
#endif

