#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

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


    return 1;
}


