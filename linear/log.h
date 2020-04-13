#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        void (*d)(const char* tag, const char *message, ...);
        void (*i)(const char* tag, const char *message, ...);
        void (*w)(const char* tag, const char *message, ...);
        void (*e)(const char* tag, const char *message, ...);
        void (*c)(const char* tag, const char *message, ...);
    } Logger;

    extern Logger Log;

    void logger_init(void);

#ifdef __cplusplus
}
#endif
#endif
