
#ifndef ZLISP_SYMBOL_H
#define ZLISP_SYMBOL_H

#include "list.h"
#include "string_utils.h"
#include "typed_pointer.h"

// semantic part
enum symbol_type {
	UNDEFINED,
	VARIABLE,
	DOTTED_PAIR,
	BUILDIN_FUNCTION,
	BUILDIN_SPECIAL_FORM,
	USER_DEFINED_FUNCTION,
	USER_DEFINED_SPECIAL_FORM,
	UNNAMED_FUNCTION,
	UNNAMED_SPECIAL_FORM,
};

struct symbol {
	string name;

	enum symbol_type type;

	// struct list*   plist;
	// struct list*   bind_list;
	typed_pointer* value;
};

INITIALIZE_POINTER(symbol, struct symbol, SYMBOLTYPE);

#endif  // ZLISP_SYMBOL_H