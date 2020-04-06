#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "../includes/common.h"

// endianness check - implementation in Linux
static union {char c[4]; long mylong;} endian_test = {{'l', '?', '?', 'b'}};
#define ENDIANNESS      ((char)endian_test.mylong)   \

// intuitive solution to check the endianness
char endianness_check(void)
{
    uint32_t a = 0x12345678;
    char *p = (char*)&a;
    if (*p == 0x78) {
        printf("little endian system\n");
        return 1;
    } else if (*p == 0x12) {
        printf("big endian system\n");
        return 0;
    }
    printf("Error: unknown endianness! \n");
    return -1;
}

// endianness switch for 32 bits data
int32_t endianness_swInt32(int32_t val)
{
    return ((val & 0xff) << 24 |        \
            (val & 0xff00) << 8 |       \
            (val & 0xff0000) >> 8 |     \
            (val & 0xff000000) >> 24);
}

// endianess switch for 16 bits data
int16_t endianness_swInt16(int16_t val)
{
    return ((val & 0xff) << 8 |         \
            (val & 0xff00) >> 8);
}

#define BITS_SHIFT32    0
#define SETBIT_SHIFT    0
#define MAGIC_NUMBER    0
#define LOOKUP_TABLE    0
#define SHIFT_LOOKUP    1

const uint8_t reverse[256] = {
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

// reverse bits of 32 bits data
uint32_t reverse_bits32(uint32_t n)
{
#if BITS_SHIFT32
    uint32_t ret = 0;
    for (int i = 0; i < 8 * sizeof(n); i++) {
        ret = (ret << 0x1) | (n & 0x1);
        n >>= 0x1;
    }
    return ret;
#elif SETBIT_SHIFT
    uint32_t ret = n;
    uint32_t cnt = 8 * sizeof(n) - 1;
    n >>= 0x1;
    while (n != 0) {
        ret = (ret << 1) | (n & 0x1);
        n >>= 1;
        cnt--;
    }2
    ret <<= cnt;
    return ret;
#elif MAGIC_NUMBER
    uint32_t ret = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    ret = ((ret & 0xcccccccc) >> 2) | ((ret & 0x33333333) << 2);
    ret = ((ret & 0xf0f0f0f0) >> 4) | ((ret & 0x0f0f0f0f) << 4);
    ret = ((ret & 0xff00ff00) >> 8) | ((ret & 0x00ff00ff) << 8);
    ret = ((ret & 0xffff0000) >> 16) | ((ret & 0x0000ffff) << 16);
    return ret;
#elif LOOKUP_TABLE
    uint32_t ret = 0;
    for (int i = 0; i < sizeof(n); i++)
        ret = (ret << 0x8) | reverse[(n >> 8*i) & 0xff];
    return ret;
#elif SHIFT_LOOKUP
    return reverse[n & 0xff] << 24 |          \
        reverse[(n >> 8) & 0xff] << 16 |    \
        reverse[(n >> 16) & 0xff] << 8 |    \
        reverse[(n >> 24) & 0xff];
#endif
}

/* Given a number x and two position (from the right side) in a binary
 * represantation of x, swaps n bits at given two positions (given that the
 * two sets of bits do not overlap)
 * Example:
 * Input -  x = 47 (00101111)
 *          p1 = 1 (2nd bit from the right)
 *          p2 = 5 (6th bit from the right)
 *          n = 3 (# of bits to be swapped)
 * Output - 11100011
 * The 3 bits starting from the 2nd bit from the right side are swapped with
 * 3 bits starting from the 6th bit from the right side
 * */
uint32_t swap_bits(uint32_t x, uint32_t p1, uint32_t p2, uint32_t n)
{
    // move all bits of first set to rightmost side
    uint32_t set1 = (x >> p1) & ((1U << n) - 1);
    // move all bits of second set to rightmost side
    uint32_t set2 = (x >> p2) & ((1U << n) - 1);
    // xor two sets
    uint32_t xor = set1 ^ set2;
    // put xor bits back to the original positions
    xor = (xor << p1) | (xor << p2);
    // xor the xor with the originial number so that the two ses are swapped
    uint32_t res = x ^ xor;

    return res;
}


int main(int argc, char* argv[])
{
    //endianess test
    if (ENDIANNESS == 'l')
        printf("This is little endian system\n");
    else if (ENDIANNESS == 'b')
        printf("This is big endian system\n");
    else
        printf("unknown endianness!\n");
    //endianness_check(); // my implementation passed test also
    int32_t n32 = 0x12ffff78;
    printf("0x12ffff78 switch to big endian: 0x%08x\n", endianness_swInt32(n32));
    int16_t n16 = 0x1234;
    printf("0x1234 sitch to big endian: 0x%04x\n\n", endianness_swInt16(n16));

    // itoa test
    uint32_t num = 0xff;
    char s1[33], s2[33], s3[33];
    printf("Hex: %s\nDec: %s\nBin: %s\n\n", itoa(num, s1, 16), itoa(num, s2, 10), itoa(num, s3, 2));
    memset(s1, 0, 33*sizeof(char));
    memset(s2, 0, 33*sizeof(char));
    memset(s3, 0, 33*sizeof(char));

    // reverse bits of 32 bits data
    // change the value of macro definition for different implementation test
    num = 0x12345678;
    uint32_t rev = reverse_bits32(num);
    printf("%s ->\n%s\n\n", itoa(num, s1, 2), itoa(rev, s2, 2));
    //printf("%d, %d \n", num, rev);
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));

    // swap bits test
    num = 47;
    uint32_t res = swap_bits(num, 1, 5, 3);
    printf("%s -> \n%s\n\n", itoa(num, s1, 2), itoa(res, s2, 2));

    return 1;
}


