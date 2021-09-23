//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_EXPRESSION_H
#define ZLISP_EXPRESSION_H

#include "string_utils.h"
#include "uthash/uthash.h"
#include <stdint.h>

enum node_type {
	ATOM,
	EXPR,
};

typedef struct element* hashed_list;
typedef hashed_list     list;

#define EMPTY_LIST NULL

#define LIST_ITER(list_name, current, tmp)                                     \
	HASH_ITER (hh, list_name, current, tmp)

struct element {
	int64_t index; /* key */

	unsigned is_cdr : 1;

	enum node_type value_type;
	union {
		list    list;
		int64_t symbol;
	} value;

	UT_hash_handle hh;
};

struct element* new_element();

enum status list_push_symbol(list*, int64_t);
enum status list_push_list(list*, list);

void clean_list(list*);
void list_deep_clean(list*);

struct element* nth(list, size_t);

#endif  // ZLISP_EXPRESSION_H
