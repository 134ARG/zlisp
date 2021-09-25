
#include "list_abandon.h"
#include "logger.h"
#include "status.h"
#include "symbol.h"
#include "uthash/uthash.h"
#include <malloc.h>
#include <stdint.h>

struct element_abandon*
new_element()
{
	struct element_abandon* p = malloc(sizeof(struct element_abandon));

	p->index        = 0;
	p->value_type   = ATOM;
	p->value.symbol = 0;
	p->is_cdr       = 0;

	return p;
}

enum status
list_push_symbol(list* list_ptr, int64_t symbol)
{
	struct element_abandon* end = NULL;

	size_t index = 0;

	index = HASH_COUNT(*list_ptr);
	HASH_FIND_INT(*list_ptr, &index, end);
	if (end && end->is_cdr) {
		LOG_ERROR("cdr of the list is set: <%p: %lu>", list_ptr, index);
		return ERR_CDR_IS_SET;
	}

	struct element_abandon* p = new_element();
	p->value_type     = ATOM;
	p->value.symbol   = symbol;
	p->index          = HASH_COUNT(*list_ptr);
	HASH_ADD_INT(*list_ptr, index, p);
	return OK;
}

enum status
list_push_list(list* list_ptr, list tail)
{
	struct element_abandon* end = NULL;

	size_t index = 0;

	index = HASH_COUNT(*list_ptr);
	HASH_FIND_INT(*list_ptr, &index, end);

	if (end) {
		if (end->is_cdr) {
			LOG_ERROR("cdr of the list is set: <%p: %lu>", list_ptr, index);
			return ERR_CDR_IS_SET;
		}
	}

	struct element_abandon* p = new_element();

	p->value_type = EXPR;
	p->value.list = tail;
	p->index      = HASH_COUNT(*list_ptr);
	HASH_ADD_INT(*list_ptr, index, p);

	return OK;
}

void
clean_list(list* list_ptr)
{
	if (*list_ptr) {
		HASH_CLEAR(hh, *list_ptr);
	}
}

void
list_deep_clean(list* list_ptr)
{
	struct element_abandon* current;
	struct element_abandon* tmp;
	HASH_ITER (hh, *list_ptr, current, tmp) {
		HASH_DEL(*list_ptr, current);
		if (current->value_type == EXPR) {
			clean_list(&(current->value.list));
			current->value.list = NULL;
		}
	}
	*list_ptr = EMPTY_LIST;
}

struct element_abandon*
nth(list lst, size_t index)
{
	if (!lst) {
		LOG_ERROR("nth: empty pointer\n");
		return NULL;
	}
	if (index >= HASH_COUNT(lst)) {
		LOG_ERROR("nth: index overbound\n");
		return NULL;
	}
	struct element_abandon* result = NULL;
	HASH_FIND_INT(lst, &index, result);

	return result;
}