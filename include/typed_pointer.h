#ifndef ZLISP_TYPED_POINTER_H
#define ZLISP_TYPED_POINTER_H

#include "status.h"
#include "logger.h"
#include <stdint.h>
#include <stdlib.h>

struct symbol;

#define NIL_TYPE 0

enum types {
	STRLITERAL,
	FLOATLITERAL,
	INTLITERAL,
	SYMBOLTYPE,
	READERCHAR,
	LIST,
	CUSTOM,
	NIL,
};

struct typed_pointer {
	int type;

	void* value;
};

typedef struct typed_pointer typed_pointer;

#define NULL_POINTER                                                           \
	(struct typed_pointer)                                                     \
	{                                                                          \
		.type = NIL, .value = NULL                                             \
	}

static struct typed_pointer
new_empty_pointer()
{
	return (struct typed_pointer){
	    .type  = NIL,
	    .value = NULL,
	};
}

static struct typed_pointer
new_pointer(enum types type)
{
	struct typed_pointer p = new_empty_pointer();
	p.type                 = type;
	return p;
}

static enum status
pointer_set(typed_pointer* p, void* s, enum types type)
{
	p->value = s;
	p->type  = type;
	return OK;
}

#define INITIALIZE_POINTER(name, T, id)                                        \
	static typed_pointer make_pointer_to##name(T* s)                           \
	{                                                                          \
		struct typed_pointer p = new_pointer(id);                              \
		pointer_set(&p, s, id);                                                \
		return p;                                                              \
	}                                                                          \
                                                                               \
	static enum status pointer_to_##name(typed_pointer p, T** s)               \
	{                                                                          \
		if (!(p.type ^ id)) {                                                  \
			*s = (T*)p.value;                                                  \
			return OK;                                                         \
		} else {                                                               \
			LOG_ERROR("to: Invalid type: expect %d, get %d",                   \
			          SYMBOLTYPE,                                              \
			          p.type);                                                 \
			*s = NULL;                                                         \
			return ERR_TYPE;                                                   \
		}                                                                      \
	}                                                                          \
                                                                               \
	static enum status pointer_set_##name(typed_pointer p, T* s)               \
	{                                                                          \
		if (!(p.type ^ id) || p.type == NIL_TYPE) {                            \
			p.type  = id;                                                      \
			p.value = s;                                                       \
			return OK;                                                         \
		} else {                                                               \
			LOG_ERROR("set: Invalid type: expect %d, get %d",                  \
			          SYMBOLTYPE,                                              \
			          p.type);                                                 \
			return ERR_TYPE;                                                   \
		}                                                                      \
	}

INITIALIZE_POINTER(float, double, FLOATLITERAL);
INITIALIZE_POINTER(int, int64_t, INTLITERAL);

#endif  // ZLISP_TYPED_POINTER_H