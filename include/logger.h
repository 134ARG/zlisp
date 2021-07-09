//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_LOGGER_H
#define ZLISP_LOGGER_H

void logger(const char* file, int line, const char* fmt,...)
		__attribute__((format(printf, 3, 4)));

#define LOG_ERROR(fmt, ...) logger(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif //ZLISP_LOGGER_H
