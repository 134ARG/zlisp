//
// Created by fort64 on 7/9/2021.
//

#include "unit_test.h"
#include "context.h"
#include "lexer.h"
#include "list.h"
#include "mem_utils.h"
#include "status.h"
#include "string_utils.h"
#include <stdio.h>

enum status
test_lexer()
{
	struct file_context test_file = file_context_new("./test.ll", "r");

	if (!test_file.file) {
		printf("Hello, World!\n");
		return 0;
	}
	string segment = make_string();
	while (next_segment(&test_file, &segment) == OK) {
		fprintf(stderr, "%s | ", segment.data);
	}
	return OK;
}

void
test_list()
{
	CLEANUP(clean_list) list list_a = EMPTY_LIST;
	CLEANUP(clean_list) list list_b = EMPTY_LIST;
	CLEANUP(clean_list) list list_c = EMPTY_LIST;

	list_push_symbol(&list_a, 1);
	list_push_symbol(&list_a, 2);
	list_push_list(&list_b, list_a);

	ASSERT(nth(list_a, 0)->value.symbol == 1);
	ASSERT(nth(list_a, 1)->value.symbol == 2);
	ASSERT(nth(list_b, 0)->value.list == list_a);

	MOVE_OUT(list_a);
	list_deep_clean(&list_b);
}