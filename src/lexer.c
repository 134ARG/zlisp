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
		if (isdigit(*ch_ptr) && state == 0) {
			state = 1;
		} else if (isdigit(*ch_ptr) &&
		           (state == 1 || state == 2 || state == 4)) {
			state = state;
		} else if (is_dot(*ch_ptr) && state == 1) {
			state = 2;
		} else if (is_exponent(*ch_ptr) && (state == 1 || state == 2)) {
			state = 3;
		} else if (isdigit(*ch_ptr) && state == 3) {
			state = 4;
		} else {
			return false;
		}
	}
	return state == 1 || state == 2 || state == 4;
}

/*
 * read_segment returns in three cases:
 * 1. EOF
 * 2. non-symbol character
 * 3. symbol string
 */
enum status
next_unit(struct file_context* ctx, string* segment)
{
	string_reset(segment);

	int ch = 0;

	// ch = skip_blanks(ctx);
	ch = file_context_getchar(ctx);
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
next_segment(struct file_context* ctx, string* segment)
{
	string_reset(segment);

	int abort_flag  = false;
	int ignore_flag = false;

	int ch = 0;

	ch = skip_blanks(ctx);
	if (ch == EOF) {
		return INFO_END_OF_FILE;
	}

	string_push(segment, ch);

	if (is_doublequote(ch)) {
		ignore_flag = true;
	} else if (!is_symbol(ch)) {
		return OK;
	}

	while ((!is_blank_or_eof(ch = file_context_getchar(ctx)) || ignore_flag) &&
	       !abort_flag) {
		if (ch == '\\') {
			ch = file_context_getchar(ctx);
		}

		string_push(segment, (char)ch);

		if (is_doublequote(ch) && ignore_flag) {
			ignore_flag = false;
			abort_flag  = true;
		}
	}

	if (ch != EOF) {
		CHECK_OK(file_context_rollback(ctx, -1));
	}

	return OK;
}