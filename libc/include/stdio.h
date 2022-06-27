#ifndef STDIO_H
#define STDIO_H 1

#include <sys/cdefs.h>
#include <stdarg.h>

#define EOF (-1)

int vprintf(const char* format, va_list list);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#endif
