
#include <string.h>
#include <stdbool.h>
#include "common.h"

static void reverse(char* s);

// A utility function to reverse a string
static void reverse(char* s)
{
    int l = 0;
    int r = strlen(s) - 1;
    while (l < r) {
        char tmp = *(s+l);
        *(s+l) = *(s+r);
        *(s+r) = tmp;
        l++;
        r--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        if (base == 10 || base == 16) {
            int rem = num % base;
            str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
            num = num / base;
        } else if (base = 2) {
            str[i++] = (num & 0x1) ? '1' : '0';
            num >>= 1;
        }
    }

    // If number is negative, append '-'
    if (base == 10 && isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str);

    return str;
}
