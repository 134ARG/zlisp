
#include "char_utils.h"
#include "context.h"
#include "lexer.h"
#include "status.h"
#include "stream.h"
#include "symbol.h"

enum status
read_token(struct file_stream* s,
           char                x,
           struct context*     ctx,
           struct token*       tok)
{
	return OK;
}

enum status
form_object(struct token* tok, struct symbol** sym)
{
	return OK;
}

enum status
reader(struct file_stream* s, struct symbol** sym_ptr, struct context* ctx)
{
	char x;

	struct readtable* rt  = ctx->rt;
	struct token      tok = make_token();

	struct symbol* new = NULL;

	while ((x = file_stream_getchar(s)) != EOF) {
		if (check_syntax_type(rt, WHITESPACE, x)) {
			// ignore blanks
			continue;
		} else if (check_syntax_type(rt, TERMINATING_MACRO_CHAR, x) ||
		           check_syntax_type(rt, NON_TERMINATING_MACRO_CHAR, x)) {
			// call corresponding reader macro function: func(stream, x, ctx);
			new = NULL;
			return OK;
		} else if (check_syntax_type(rt, SINGLE_ESCAPE, x)) {
			x = file_stream_getchar(s);
			CHECK_OK(read_token(s, x, ctx, &tok));
			CHECK_OK(form_object(&tok, &new));
			return OK;
		} else if (check_syntax_type(rt, MULTIPLE_ESCAPE, x)) {
			// TODO(134ARG)
			new = NULL;
			return OK;
		} else {
			LOG_ERROR("reader: unrecognized char: %c", x);
			return ERR_LEXER;
		}
	}

	(*sym_ptr) = new;
	return INFO_END_OF_FILE;

	// return OK;
}