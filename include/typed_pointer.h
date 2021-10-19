#include "string_utils.h"

enum types {
	STRLITERAL,
	FLOATLITERAL,
	INTLITERAL,
	SYMBOLTYPE,
	READERCHAR,
	LIST,
	NIL,
	CUSTOM,
};


struct typed_pointer {
	enum types type;

	union {
		struct symbol* symbol;
		double*        float_literal;
		long*          int_literal;
		char*          string_literal;
		char*          reader_char;
		struct list*   list;
		int            nil;
		void*          custom;
	} value;
};

typedef struct typed_pointer typed_pointer;

#define NULL_POINTER                                                           \
	(struct typed_pointer)                                                     \
	{                                                                          \
		.type = NIL, .value.nil = 1                                            \
	}

static struct typed_pointer*
new_empty_pointer()
{
	struct typed_pointer* p = malloc(sizeof(struct typed_pointer));
	p->type                 = NIL;
	p->value.nil            = 1;
	return p;
}

static struct typed_pointer*
new_pointer(enum types type)
{
	struct typed_pointer* p = new_empty_pointer();
	p->type                 = type;
	return p;
}