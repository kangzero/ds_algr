#ifndef __BITS_H__
#define __BITS_H__

#include <stdint.h>

char endianness_check(void);
int32_t endianness_swInt32(int32_t val);
int16_t endianness_swInt16(int16_t val);
uint32_t reverse_bits32(uint32_t n);

#endif
