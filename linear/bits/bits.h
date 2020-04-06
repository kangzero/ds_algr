#ifndef __BITS_H__
#define __BITS_H__

#include <stdint.h>

char endianness_check(void);
int32_t endianness_swInt32(int32_t val);
int16_t endianness_swInt16(int16_t val);
uint32_t reverse_bits32(uint32_t n);
uint32_t swap_bits(uint32_t x, uint32_t p1, uint32_t p2, uint32_t n);
uint32_t swap_two_bits(uint32_t n, uint32_t p1, uint32_t p2);
uint32_t msb_int32(uint32_t n);
uint32_t toggle_middle_bits(uint32_t n);
uint32_t toggle_between_idx(uint32_t n, uint32_t l, uint32_t r);
#endif
