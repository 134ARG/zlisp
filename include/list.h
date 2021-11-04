#ifndef ZLISP_LIST_H
#define ZLISP_LIST_H

#include "typed_pointer.h"
#include "uthash/uthash.h"

struct list_hash_index {
	size_t       index; /* key */
	struct list* node;

	UT_hash_handle hh;
};

struct list {
	struct typed_pointer car;
	struct typed_pointer cdr;

	struct list_hash_index* hash;

	int flag_indexed;
};

INITIALIZE_POINTER(list, struct list, LIST);

struct list  make_list();
struct list* new_list();

enum status clean_list(struct list* lst);
enum status delete_list(struct list* lst);

enum status car(const struct list* lst, typed_pointer elt);
enum status cdr(const struct list* lst, typed_pointer rest);
enum status append(struct list* lst, struct list* tail);
enum status cons(struct typed_pointer* car,
                 struct typed_pointer* cdr,
                 struct list*          lst);

#endif  // ZLISP_LIST_H