//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_LOGGER_H
#define ZLISP_LOGGER_H

#include <stdarg.h>
#include <stdio.h>

void set_log_level(unsigned int level);

void
logger(unsigned int level, const char* file, int line, const char* fmt, ...)
    __attribute__((format(printf, 4, 5)));

#define LOG_ERROR(fmt, ...) logger(2, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) logger(1, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...) logger(0, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif  // ZLISP_LOGGER_H
