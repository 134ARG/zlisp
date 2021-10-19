#include "string_utils.h"
#include "symbol.h"

#define NIL_TYPE 0

enum types {
	STRLITERAL,
	FLOATLITERAL,
	INTLITERAL,
	SYMBOLTYPE,
	READERCHAR,
	LIST,
	CUSTOM,
};

struct typed_pointer {
	long type;

	void* value;
};

typedef struct typed_pointer typed_pointer;

#define NULL_POINTER                                                           \
	(struct typed_pointer)                                                     \
	{                                                                          \
		.type = NIL_TYPE, .value = NULL                                        \
	}

#define INITIALIZE_POINTER(name, T, id)                                        \
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
			*s = NULL;                                                         \
			return ERR_TYPE;                                                   \
		}                                                                      \
	}

INITIALIZE_POINTER(symbol, struct symbol, SYMBOLTYPE)

static struct typed_pointer*
new_empty_pointer()
{
	struct typed_pointer* p = malloc(sizeof(struct typed_pointer));
	p->type                 = NIL_TYPE;
	p->value                = NULL;
	return p;
}

static struct typed_pointer*
new_pointer(enum types type)
{
	struct typed_pointer* p = new_empty_pointer();
	p->type                 = type;
	return p;
}
