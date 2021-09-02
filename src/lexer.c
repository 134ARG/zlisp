//
// Created by zry on 2021/7/8.
//

#include "lexer.h"
#include "char_utils.h"
#include "context.h"
#include "status.h"
#include "string_utils.h"
#include <ctype.h>

#define false 0
#define true 1

static int
skip_blanks(struct file_context* ctx)
{
	int ch = file_context_getchar(ctx);
	if (is_blank(ch)) {
		while (is_blank(ch)) {
			ch = file_context_getchar(ctx);
		}
	}
	return ch;
}

/*
 * Check if the segment is a valid number of the form:
 * digits(. digits)(e digits)
 * using a FDA.
 */
int
is_number_token(const string segment)
{
	unsigned state = 0;

	size_t start = 0;

	if (is_sign(segment.data[0])) {
		start = 1;
	}

	STRING_ITER_FROM (segment, ch_ptr, start) {
		if (isalnum(*ch_ptr) && state == 0) {
			state = 1;
		} else if (isalnum(*ch_ptr) &&
		           (state == 1 || state == 2 || state == 4)) {
			state = state;
		} else if (is_dot(*ch_ptr) && state == 1) {
			state = 2;
		} else if (is_exponent(*ch_ptr) && (state == 1 || state == 2)) {
			state = 3;
		} else if (isalnum(*ch_ptr) && state == 3) {
			state = 4;
		} else {
			return false;
		}
	}
	return state == 1 || state == 2 || state == 4;
}

enum token_type
select_token(const string segment)
{
	if (!string_compare_cstr(segment, "(")) {
		return LPARAN;
	} else if (!string_compare_cstr(segment, ")")) {
		return RPARAN;
	} else if (!string_compare_cstr(segment, ",")) {
		return COMMA;
	} else if (!string_compare_cstr(segment, ":")) {
		return COLON;
	} else if (!string_compare_cstr(segment, ";")) {
		return SEMICOLON;
	} else if (!string_compare_cstr(segment, "'")) {
		return QUOTE;
	} else if (!string_compare_cstr(segment, "`")) {
		return BACKQUOTE;
	} else if (!string_compare_cstr(segment, "\"")) {
		return DOUBLEQUOTE;
	} else {
		return STRING;
	}
}

/*
 * read_segment returns in three cases:
 * 1. EOF
 * 2. non-symbol character
 * 3. symbol string
 */
enum status
next_segment(struct file_context* ctx, string* segment)
{
	string_reset(segment);

	int ch = 0;

	ch = skip_blanks(ctx);
	if (ch == EOF) {
		return INFO_END_OF_FILE;
	}

	string_push(segment, (char)ch);
	if (!is_symbol(ch)) {
		return OK;
	}

	while (is_symbol(ch = file_context_getchar(ctx))) {
		if (ch == '\\') {
			ch = file_context_getchar(ctx);
		}
		string_push(segment, (char)ch);
	}

	if (ch != EOF) {
		CHECK_OK(file_context_rollback(ctx, -1));
	}
	return OK;
}

enum status
next_token(struct file_context* ctx, struct token* token)
{
	token->type = 0;
	string_reset(&token->content);

	int in_string = false;

	int ch = 0;

	ch = skip_blanks(ctx);
	if (ch == EOF) {
		return INFO_END_OF_FILE;
	}

	string_push(&token->content, ch);

	if (is_doublequote(ch)) {
		in_string = true;
	}

	while (!is_blank_or_eof(ch = file_context_getchar(ctx)) || in_string) {
		if (ch == '\\') {
			ch = file_context_getchar(ctx);
		} else if (ch == is_doublequote(ch) && in_string) {
			in_string = false;
		}
		string_push(&token->content, (char)ch);
	}

	if (ch != EOF) {
		CHECK_OK(file_context_rollback(ctx, -1));
	}

	if (is_number_token(token->content)) {
		token->type = NUMBER;
	} else {
		token->type = BAD_TOEKN;
		return ERR_INVALID_DATA;
	}
	return OK;
}