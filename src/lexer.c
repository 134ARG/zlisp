//
// Created by zry on 2021/7/8.
//

#include "lexer.h"
#include "char_utils.h"
#include "check.h"
#include "context.h"
#include "list.h"
#include "logger.h"
#include "status.h"
#include "string_utils.h"
#include <ctype.h>

#define false 0
#define true 1

struct token
make_token()
{
	return (struct token){
	    .type    = BAD_TOKEN,
	    .content = make_string(),
	};
}

enum status
clean_token(struct token* token)
{
	CHECK_OK(clean_string(&token->content));
	token->type = BAD_TOKEN;
	return OK;
}

enum status
skip_blanks(struct file_context* ctx)
{
	int ch = 0;
	while (is_blank(ch = file_context_getchar(ctx)))
		;
	if (ch != EOF) {
		CHECK_OK(file_context_rollback(ctx, -1));
	}
	return OK;
}

enum status
skip_to_blank(struct file_context* ctx)
{
	int ch = 0;
	while (!is_blank_or_eof(ch = file_context_getchar(ctx)))
		;
	return OK;
}

/*
 * Check if the segment is a valid number of the form:
 * digits(. digits)(e digits)
 * using a DFA.
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
	if (!segment) {
		return ERR_NULL_PTR;
	}

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

enum token_type
switch_single_char_token(int ch)
{
	if (is_lparen(ch)) {
		return LPARAN;
	} else if (is_rparen(ch)) {
		return RPARAN;
	} else if (is_colon(ch)) {
		return COLON;
	} else if (is_semi(ch)) {
		return SEMICOLON;
	} else if (!is_blank_or_eof(ch)) {
		return MACROCHAR;
	} else {
		return BAD_TOKEN;
	}
}

enum status
read_segment(struct file_context* ctx,
             string*              segment,
             int                  with_all,
             int                  with_escape,
             int (*read_predicate)(int),
             int (*terminate_predicate)(int))
{
	int ch             = 0;
	int terminate_flag = false;

	if (!read_predicate) {
		read_predicate = is_symbol;
	}

	while ((read_predicate(ch = file_context_getchar(ctx)) || with_all) &&
	       !terminate_flag) {
		if (terminate_predicate && terminate_predicate(ch)) {
			terminate_flag = true;
		}
		if (with_escape && is_slash(ch)) {
			ch = file_context_getchar(ctx);
		}
		// TODO: utf characters support
		CHECK_OK(string_push(segment, (char)ch));
	}

	if (ch != EOF) {
		CHECK_OK(file_context_rollback(ctx, -1));
	}

	// skip_to_blank(ctx);

	return OK;
}

enum status
next_token(struct file_context* ctx, struct token* token)
{
	if (!token) {
		return ERR_NULL_PTR;
	}
	string* content = &token->content;
	string_reset(content);

	int abort_flag = false;
	int with_all   = false;

	int ch = 0;

	// CHECK_OK(skip_blanks(ctx));
	ch = file_context_getchar(ctx);
	if (ch == EOF) {
		return INFO_END_OF_FILE;
	}

	string_push(content, ch);

	if (is_doublequote(ch)) {
		with_all = true;
		CHECK_OK(
		    read_segment(ctx, content, with_all, true, NULL, is_doublequote));
		token->type = STRING;
	} else if (is_number_start(ch)) {
		with_all = false;
		CHECK_OK(read_segment(ctx, content, with_all, false, is_number, NULL));
		if (is_number_token(token->content)) {
			token->type = NUMBER;
		} else {
			token->type = BAD_TOKEN;
		}
	} else if (is_symbol(ch)) {
		with_all = false;
		CHECK_OK(read_segment(ctx,
		                      content,
		                      with_all,
		                      true,
		                      any_but_eof_and_blank,
		                      NULL));
		token->type = SYMBOL;
	} else if (is_blank(ch)) {
		skip_blanks(ctx);
		CHECK_OK(string_pop(&token->content, NULL));
		token->type = BLANK;
	} else {
		token->type = switch_single_char_token(ch);
	}

	return OK;
}

enum status
read_sexpression(struct file_context* ctx, struct list* sexpr)
{
	struct token tok = make_token();
	CHECK_OK(next_token(ctx, &tok));
	if (tok.type != LPARAN) {
		LOG_ERROR("Invalid s-exprssion");
		return ERR_LEXER;
	}
	// TODO: implement
	while (tok.type != RPARAN && next_token(ctx, &tok) == OK) {
		break;
	}
	return OK;
}