
#include <string.h>
#include <stdbool.h>
#include <limits.h>
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

// int to string
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
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (base == 10 && isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str);

    return str;
}

// string to int32
int32_t atoi(char* s)
{
    uint32_t n = strlen(s);
    uint32_t idx = 0;

    // return 0 for an empty string
    if (s == NULL) return 0;

    // remove all spaces before 1st valid char
    while (idx < n && s[idx] == ' ') {
        idx++;
        if (idx == n)
            return 0;
    }

    // 1st char is not a valid input
    if (s[idx] != '+' && s[idx] != '-' && (s[idx] < '0' || s[idx] > '9'))
        return 0;

    // check the sign flag
    char sign = 1;
    if (s[idx] == '+') {
        idx++;
    } else if (s[idx] == '-') {
        sign = -1;
        idx++;
    }

    // save the number input
    long ret = 0;
    while (idx < n) {
        if (s[idx] < '0' || s[idx] > '9') break;
        ret = 10 * ret + s[idx] - '0';
        if (ret * sign < INT_MIN)
            return INT_MIN;
        if (ret * sign > INT_MAX)
            return INT_MAX;
        idx++;
    }

    return ret * sign;
}


