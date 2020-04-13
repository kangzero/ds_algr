#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../log.h"
#include "mem.h"

#define TAG     "MEM"

typedef int word;       // word used for optimal copy speed

#define wsize   sizeof(word)
#define wmask   (wsize - 1)

// copy a block of memory, handling overlap
void* nk_memcpy(void* dst0, const void* src0, size_t length)
{
    char *dst = dst0;
    const char *src = src0;
    size_t t;

    if (length  == 0 || dst == src)
        goto done;
    // Marcros: loop-t-times; and loop-t-times, t>0
#define TLOOP(s)    if (t) TLOOP1(s)
#define TLOOP1(s)   do {s;} while(--t)

    if ((uintptr_t)dst <= (uintptr_t)src || (uintptr_t)src + length <= (uintptr_t)dst ) {
        t = (uintptr_t)src; // only need low bits
        if ((t | (uintptr_t)dst) & wmask) {
            // alignment is innnecessray for some of architecutre, like x86, ARM cortex, etc..
            // try to align operands. This cannot be done unless the low bits match
            if ((t ^ (uintptr_t)dst) & wmask || length < wsize)
                t = length;
            else
                t = wsize - (t & wmask);
            length -= t;
            TLOOP1(*dst++ = *src++);
        }
        // copy whole wods, then mop up any trailing bytes
        t = length / wsize;
        TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
        t = length & wmask;
        TLOOP(*dst++ = *src++);
    } else {
        // copy backwards. Otherwise essentially the same.
        src += length;
        dst += length;
        t = (uintptr_t)src;
        if ((t | (uintptr_t)dst) & wmask) {
            if ((t ^ (uintptr_t)dst) & wmask || length < wsize)
                t = length;
            else
                t &= wmask;
            length -= t;
            TLOOP1(*--dst = *--src);
        }

        t = length / wsize;
        TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
        t = length & wmask;
        TLOOP(*--dst = *src);
    }

done:
    return dst0;
}

// implementation by musl
int nk_memcmp(const void* vl, const void* vr, size_t n)
{
    const unsigned char *l = vl, *r = vr;
    for (; n && *l == *r; n--, l++, r++);
    return n ? *l - *r : 0;

}

// leverage by nk_memcpy
void* nk_memmove(void* s1, const void* s2, size_t n)
{
    return nk_memcpy(s1, s2, n);
}

void* nk_memset(void* dst, int c, size_t n)
{
#if 0 // set byte by byte
    if (!n) return dst;

    int i = 0;
    while (i != n) {
        *(uint8_t*)(dst + i) = c;
        i++;
    }

    return dst;
#else
    unsigned char *s = dst;
    size_t k;

    // Fill head and tail with minimal branching. Each conditional ensures that all the subsequently
    // used offsets are well-defined and in the dest region
    if (!n) return dst;
    s[0] = s[n-1] = c;
    if (n <= 2) return dst;
    s[1] = s[n-2] = c;
    s[2] = s[n-3] = c;
    if (n <= 6) return dst;
    s[3] = s[n-4] = c;
    if (n <= 8) return dst;

    // Advanced pointer to align it a 4-byte boundary, and truncate n to a multiple of 4.
    // The previous code already took car of any head/tail that get cut off by the alignment
    k = -(uintptr_t)s & 3;
    s += k;
    n -= k;
    n &= -4;
    n /= 4;

    uint32_t *ws = (uint32_t*)s;
    uint32_t wc = c & 0xff;
    wc |= ((wc << 8) | (wc << 16) | (wc << 24));

    for (; n; n--, ws++) *ws = wc;

    return dst;
#endif
}

int mem_test(void)
{
    Log.i(TAG, "==== Memory Test Start ====\n");

    const char src[] = "Don’t grieve. Anything you lose comes round in another form. ---By Rumi";
    uint32_t len = sizeof(src);

    char dst[128];
    if (!nk_memcpy(dst, src, len+1))
        return -1;
    Log.i(TAG, "Copy from src to dst");
    Log.i(TAG, "src string: %s", src);
    Log.i(TAG, "dst string: %s", dst);
    int len1 = 0;
    while(dst[len1++] != '\0');
    Log.i(TAG, "src length = %d, dst length = %d\n", len, len1);

    Log.i(TAG, "String dst Vs src");
    int c = nk_memcmp(dst, src, len);
    if (c > 0) {
        Log.i(TAG, "dst > src\n");
    } else if (c < 0) {
        Log.i(TAG, "dst < src\n");
    } else {
        Log.i(TAG, "dst == src\n");
    }

    if (!nk_memset(dst, 'a', 13*sizeof(char)))
        return -1;
    //*(dst + len + 1) = '\0';
    Log.i(TAG, "Set first 13 chars of string to 'a'");
    Log.i(TAG, "src: %s", src);
    Log.i(TAG, "dst: %s\n", dst);

    if (!nk_memmove(dst, src, len+1))
        return -1;
    Log.i(TAG, "Move string from src:");
    Log.i(TAG, "src: %s", src);
    Log.i(TAG, "dst: %s\n", dst);

    Log.i(TAG, "==== Memory Test End ====\n");

    return 1;
}
