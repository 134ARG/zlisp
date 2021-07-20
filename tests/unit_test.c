//
// Created by fort64 on 7/9/2021.
//

#include "status.h"
#include "context.h"
#include "string_utils.h"
#include "list.h"
#include "lexer.h"
#include "unit_test.h"
#include <stdio.h>

enum status
test_lexer()
{
	struct file_context test_file = file_context_new(
			"/home/xen134/zlisp/cmake-build-debug/test.file", "r");
	if (!test_file.file) {
		printf("Hello, World!\n");
		return 0;
	}
	string segment = read_segment(&test_file);
	while (segment.size != 0) {
		fprintf(stderr, "%s, ", segment.data);
		string_clean(&segment);
		segment = read_segment(&test_file);
	}
	return OK;
}

void 
test_list()
{
	list* list_a;
	list* list_b;
	list* list_c;

	list_a = new_list();
	list_b = new_list();
	list_c = new_list();

	list_push_symbol(list_a, 1);
	list_push_symbol(list_a, 2);
	list_push_list(list_b, list_a);

	ASSERT(nth(list_a, 0)->value.symbol == 1);
	ASSERT(nth(list_a, 1)->value.symbol == 2);
	ASSERT(nth(list_b, 0)->value.list == list_a);

	list_clean(list_a);
	list_deep_clean(list_b);
	list_destruct(list_c);
	list_destruct(list_b);

}