#include "list.h"
#include "logger.h"
#include "status.h"
#include <malloc.h>

struct list
make_list()
{
	return (struct list){
	    .car          = NULL_POINTER,
	    .cdr          = NULL_POINTER,
	    .hash         = NULL,
	    .flag_indexed = 0,
	};
}

struct list*
new_list()
{
	struct list* p = malloc(sizeof(struct list));

	p->car          = NULL_POINTER;
	p->cdr          = NULL_POINTER;
	p->hash         = NULL;
	p->flag_indexed = 0;

	return p;
}

enum status
clean_list(struct list* lst)
{
	return OK;
}

enum status
delete_list(struct list* lst)
{
	if (lst) {
		clean_list(lst);
		free(lst);
	} else {
		LOG_ERROR("Delete list: NULL pointer.");
	}

	return OK;
}

enum status
car(const struct list* lst, typed_pointer elt)
{
	elt = lst->car;
	return OK;
}

enum status
cdr(const struct list* lst, typed_pointer rest)
{
	rest = lst->cdr;
	return OK;
}

enum status
append(struct list* lst, struct list* tail)
{
	 
}