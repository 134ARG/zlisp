//
// Created by zry on 2021/7/8.
//

#include "string_utils.h"
#include "context.h"
#include "char_utils.h"

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

string
read_segment(struct file_context* ctx)
{
	string segment = string_new();

	int ch = skip_blanks(ctx);
	if (ch == EOF) return segment;
	string_push(&segment, (char) ch);
	if (!is_symbol(ch)) return segment;
	ch = file_context_getchar(ctx);
	while (is_symbol(ch)) {
		if (ch == '\\') {
			ch = file_context_getchar(ctx);
		}
		string_push(&segment, (char) ch);
		ch = file_context_getchar(ctx);
	}
	file_context_rollback(ctx, -1);
	return segment;
}