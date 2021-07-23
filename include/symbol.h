
#ifndef ZLISP_SYMBOL_H
#define ZLISP_SYMBOL_H

#include "string_utils.h"

enum symbol_type {
	UNDEFINED,
	VARIABLE,
	NUMBER,
	DOTTED_PAIR,
	BUILDIN_FUNCTION,
	BUILDIN_SPECIAL_FORM,
	USER_DEFINED_FUNCTION,
	USER_DEFINED_SPECIAL_FORM,
	UNNAMED_FUNCTION,
	UNNAMED_SPECIAL_FORM,
};

struct symbol {
	string           name;
	enum symbol_type type;
	// plist
	// bind list
	// value
};

#endif  // ZLISP_SYMBOL_H