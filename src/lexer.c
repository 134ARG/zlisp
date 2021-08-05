//
// Created by zry on 2021/7/8.
//

#include "char_utils.h"
#include "context.h"
#include "status.h"
#include "string_utils.h"

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
 * read_segment returns in three cases:
 * 1. EOF
 * 2. non-symbol character
 * 3. symbol string
 */
enum status
next_segment(struct file_context* ctx, string* segment)
{
	string_reset(segment);

	int ch;

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

	CHECK_OK(file_context_rollback(ctx, -1));
	return OK;
}