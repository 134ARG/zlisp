//
// Created by fort64 on 7/9/2021.
//

#include "unit_test.h"
#include "stream.h"
#include "lexer.h"
#include "linear_queue.h"
// #include "list_abandon.h"
#include "logger.h"
#include "mem_utils.h"
#include "status.h"
#include "string_utils.h"
#include "symbol.h"
#include "tables.h"
#include <stdio.h>

INITIALIZE_QUEUE(int_queue, int);

void
test_lexer()
{
	// next_unit
	fprintf(stderr, "start testing next_unit()\n");

	CLEANUP(clean_file_stream)
	struct file_stream test_file = make_file_stream("./test.ll", "r");

	if (!test_file.file) {
		printf("file reading failed\n");
		return;
	}
	string segment = make_string();
	while (next_unit(&test_file, &segment) == OK) {
		fprintf(stderr, "%s | ", segment.data);
	}
	clean_file_stream(&test_file);
	fprintf(stderr, "\ntesting finished.\n\n");

	// next token
	fprintf(stderr, "start testing next_token()\n");
	test_file = make_file_stream("./test.ll", "r");
	if (!test_file.file) {
		LOG_ERROR("file reading failed\n");
		return;
	}
	struct token token = make_token();
	while (next_token(&test_file, &token) != INFO_END_OF_FILE) {
		fprintf(stderr, "%s - %d | ", token.content.data, token.type);
	}
	clean_file_stream(&test_file);
	fprintf(stderr, "\ntesting finished.\n\n");
	return;
}

// void
// test_list()
// {
// 	fprintf(stderr, "start testing list\n");
// 	CLEANUP(clean_list) list list_a = EMPTY_LIST;
// 	CLEANUP(clean_list) list list_b = EMPTY_LIST;
// 	CLEANUP(clean_list) list list_c = EMPTY_LIST;

// 	list_push_symbol(&list_a, 1);
// 	list_push_symbol(&list_a, 2);
// 	list_push_list(&list_b, list_a);

// 	ASSERT(nth(list_a, 0)->value.symbol == 1);
// 	ASSERT(nth(list_a, 1)->value.symbol == 2);
// 	ASSERT(nth(list_b, 0)->value.list == list_a);

// 	MOVE_OUT(list_a);
// 	list_deep_clean(&list_b);
// 	fprintf(stderr, "testing finished.\n\n");
// }

void
test_tables()
{
	fprintf(stderr, "start testing tables.\n");
	CLEANUP(clean_symbol_table) struct symbol_table table;

	table.symbols_by_id = table.symbols_by_name = NULL;
	table.size                                  = 0;

	struct symbol new = (struct symbol){
	    .name = make_string_from_cstr("first-symbol"),
	    .type = VARIABLE,
	    // .value._integer = 10,
	};

	size_t id1 = symbol_table_add(&table, new);

	// new.value._integer = 11;
	new.name = make_string_from_cstr("second-symbol");

	size_t id2 = symbol_table_add(&table, new);

	ASSERT(id1 == 0);
	ASSERT(id2 == 1);

	struct symbol* get1;
	struct symbol* get2;

	ASSERT_OK(symbol_table_id_get(table, 0, &get1));
	ASSERT_OK(symbol_table_name_get(table,
	                                make_string_from_cstr("second-symbol"),
	                                &get2));

	ASSERT(strcmp(get1->name.data, "first-symbol") == 0);
	ASSERT(strcmp(get2->name.data, "second-symbol") == 0);
	fprintf(stderr, "testing finished.\n\n");
}

void
test_queue()
{
	fprintf(stderr, "start testing queue.\n");

	CLEANUP(clean_int_queue) struct int_queue q = make_int_queue();

	int element = 0;

	ASSERT_OK(int_queue_push(&q, 1));
	ASSERT_OK(int_queue_push(&q, 2));
	ASSERT(q.end == 2);
	ASSERT_OK(int_queue_get(&q, &element));
	ASSERT(element == 1);
	ASSERT_OK(int_queue_get(&q, &element));
	ASSERT(element == 2);
	ASSERT(is_int_queue_empty(&q));
	ASSERT(q.start == q.end);

	for (int i = 0; i < 100; i++) {
		ASSERT_OK(int_queue_push(&q, 7));
	}

	for (int i = 0; i < 100; i++) {
		ASSERT_OK(int_queue_get(&q, &element));
	}

	ASSERT(is_int_queue_empty(&q));

	fprintf(stderr, "testing finished.\n\n");
}