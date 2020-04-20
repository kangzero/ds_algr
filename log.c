#include <stdarg.h>
#include <stdio.h>

#include "log.h"

Logger Log;
char buf_format[128];
char buf_output[256];

void log_commom(const char type, const char* tag, const char* format, va_list vl);
void log_debug(const char* tag, const char* format, ...);
void log_info(const char* tag, const char* format, ...);
void log_warn(const char* tag, const char* format, ...);
void log_error(const char* tag, const char* format, ...);
void log_custom(const char* tag, const char* format, ...);

void logger_init(void)
{
    Log.d = log_debug;
    Log.i = log_info;
    Log.w = log_warn;
    Log.e = log_error;
    Log.c = log_custom;
}

void log_common(const char type, const char* tag, const char* format, va_list vl)
{
    int i = snprintf(buf_format, 128, "%c [%s] %s\r\n", type, tag, format);
    if (0 < i && i < 128) {
        i = vsnprintf(buf_output, 256, buf_format, vl);
        if (i >= 256) {
            buf_output[255] = '\0'; // truncated
        }
        if (i > 0)
            printf("%s", buf_output);
    }
}

void log_debug(const char* tag, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    log_common('D', tag, format, vl);
    va_end(vl);
}

void log_info(const char* tag, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    log_common('I', tag, format, vl);
    va_end(vl);
}

void log_warn(const char* tag, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    log_common('W', tag, format, vl);
    va_end(vl);
}

void log_error(const char* tag, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    log_common('E', tag, format, vl);
    va_end(vl);
}

void log_custom(const char* tag, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    int i = snprintf(buf_format, 128, "C [%s] %s", tag, format);
    if (0 < i && i < 128) {
        i = vsnprintf(buf_output, 256, buf_format, vl);
        if (i >= 256) {
            buf_output[255] = '\0'; // truncated
        }
        if (i > 0)
            printf("%s", buf_output);
    }
    va_end(vl);
}


