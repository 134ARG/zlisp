//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_LOGGER_H
#define ZLISP_LOGGER_H

#include <stdarg.h>
#include <stdio.h>

static void logger(const char* file, int line, const char* fmt, ...)
    __attribute__((format(printf, 3, 4)));

#define LOG_ERROR(fmt, ...) logger(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

static void
logger(const char* file, int line, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	fprintf(stderr, "%s: %d: ", file, line);
	vfprintf(stderr, fmt, args);

	va_end(args);
}

#endif  // ZLISP_LOGGER_H
