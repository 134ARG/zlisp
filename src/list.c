
#include "list.h"
#include "logger.h"
#include "status.h"
#include "symbol.h"
#include "uthash/uthash.h"
#include <malloc.h>
#include <stdint.h>

struct element*
new_element()
{
	struct element* p = malloc(sizeof(struct element));

	p->index        = 0;
	p->value_type   = ATOM;
	p->value.symbol = 0;
	p->is_cdr       = 0;

	return p;
}

list*
new_list()
{
	list* p = calloc(1, sizeof(list));
	return p;
}

enum status
list_push_symbol(list* list_ptr, int64_t symbol)
{
	struct element* end = NULL;

	size_t index = 0;

	index = HASH_COUNT(*list_ptr);
	HASH_FIND_INT(*list_ptr, &index, end);
	if (end && end->is_cdr) {
		LOG_ERROR("cdr of the list is set: <%p: %lu>", list_ptr, index);
		return ERR_CDR_IS_SET;
	}

	struct element* p = new_element();
	p->value_type     = ATOM;
	p->value.symbol   = symbol;
	p->index          = HASH_COUNT(*list_ptr);
	HASH_ADD_INT(*list_ptr, index, p);
	return OK;
}

enum status
list_push_list(list* list_ptr, list* tail)
{
	struct element* end = NULL;

	size_t index = 0;

	index = HASH_COUNT(*list_ptr);
	HASH_FIND_INT(*list_ptr, &index, end);

	if (end) {
		if (end->is_cdr) {
			LOG_ERROR("cdr of the list is set: <%p: %lu>", list_ptr, index);
			return ERR_CDR_IS_SET;
		}
	}

	struct element* p = new_element();

	p->value_type = EXPR;
	p->value.list = tail;
	p->index      = HASH_COUNT(*list_ptr);
	HASH_ADD_INT(*list_ptr, index, p);

	return OK;
}

void
list_clean(list* list_ptr)
{
	HASH_CLEAR(hh, *list_ptr);
}

void
list_destruct(list* list_ptr)
{
	list_clean(list_ptr);
	free(list_ptr);
}

void
list_deep_clean(list* list_ptr)
{
	struct element* current;
	struct element* tmp;
	HASH_ITER (hh, *list_ptr, current, tmp) {
		HASH_DEL(*list_ptr, current);
		if (current->value_type == EXPR) {
			list_destruct(current->value.list);
		}
	}
}

struct element*
nth(list* list_ptr, size_t index)
{
	if (!list_ptr) {
		LOG_ERROR("nth: empty pointer\n");
		return NULL;
	}
	if (index >= HASH_COUNT(*list_ptr)) {
		LOG_ERROR("nth: index overbound\n");
		return NULL;
	}
	struct element* result = NULL;
	HASH_FIND_INT(*list_ptr, &index, result);

	return result;
}