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

#define ASSERT_OK(EXPR) ASSERT((EXPR) == OK);

void test_lexer();
void test_list();
void test_tables();
void test_next_token();
void test_queue();

#endif  // ZLISP_UNIT_TEST_H