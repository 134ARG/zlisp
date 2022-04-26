#ifndef ZLISP_CONTEXT_H
#define ZLISP_CONTEXT_H

#include "char_utils.h"

// placeholder temporarily
struct context {
	// parent context
	struct context* parent_context;
	// child context
	struct context* child_context;

	struct readtable* rt;
};

#endif  // ZLISP_CONTEXT_H