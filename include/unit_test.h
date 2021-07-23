//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_UNIT_TEST_H
#define ZLISP_UNIT_TEST_H

#include "logger.h"
#include "status.h"

#define ASSERT(COND)                                                           \
	do {                                                                       \
		if (!(COND)) {                                                         \
			LOG_ERROR("failed: %s\n", #COND);                                  \
		}                                                                      \
	} while (0)

enum status test_lexer();

void test_list();

#endif  // ZLISP_UNIT_TEST_H