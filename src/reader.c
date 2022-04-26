
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
	string_push(&tok->content, x);
	struct readtable* rt = ctx->rt;

	x = file_stream_getchar(s);

	while (!check_syntax_type(rt, TERMINATING_MACRO_CHAR, x) &&
	       !check_syntax_type(rt, WHITESPACE, x)) {
		if (check_syntax_type(rt, CONSTITUENT, x) ||
		    check_syntax_type(rt, NON_TERMINATING_MACRO_CHAR, x)) {
			string_push(&tok->content, x);
		} else if (check_syntax_type(rt, SINGLE_ESCAPE, x)) {
			x = file_stream_getchar(s);
			string_push(&tok->content, x);
		} else {
			LOG_ERROR("reader: invalid char in token: %c", x);
			return ERR_LEXER;
		}
		x = file_stream_getchar(s);
	}

	CHECK_OK(file_stream_rollback(s, -1));
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
			// here only store the char into tok
			string_push(&tok.content, x);
			new = NULL;
			break;
		} else if (check_syntax_type(rt, SINGLE_ESCAPE, x)) {
			x = file_stream_getchar(s);
			CHECK_OK(read_token(s, x, ctx, &tok));
			CHECK_OK(form_object(&tok, &new));
			return OK;
		} else if (check_syntax_type(rt, MULTIPLE_ESCAPE, x)) {
			// TODO(134ARG)
			new = NULL;
			break;
		} else if (check_syntax_type(rt, CONSTITUENT, x)) {
			CHECK_OK(read_token(s, x, ctx, &tok));
			CHECK_OK(form_object(&tok, &new));
			break;
		} else {
			LOG_ERROR("reader: unrecognized char: %c", x);
			return ERR_LEXER;
		}
	}

	// debug
	fprintf(stderr, "test: read result: %s\n", tok.content.data);
	clean_token(&tok);

	(*sym_ptr) = new;

	if (x == EOF) {
		return INFO_END_OF_FILE;
	}
	return OK;
}
