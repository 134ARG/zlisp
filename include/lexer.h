//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_LEXER_H
#define ZLISP_LEXER_H

#include "context.h"
#include "linear_queue.h"
#include "string_utils.h"

enum token_type {
	BAD_TOKEN,  // mal-formed segment

	LPARAN,  // (
	RPARAN,  // )

	COLON,      // :
	SEMICOLON,  // ;

	SYMBOL,     // symbol
	STRING,     // "something like that"
	NUMBER,     // 123.4 or 1234 or 123e3
	MACROCHAR,  // `, ', # or other characters used for macro
	BLANK,
};

struct token {
	enum token_type type;
	string          content;
};

INITIALIZE_QUEUE(token_queue, struct token);

struct token make_token();

enum status clean_token(struct token* token);

enum status next_unit(struct file_context* ctx, string* segment);
enum status next_segment(struct file_context* ctx, string* segment);
enum status next_token(struct file_context* ctx, struct token* token);

#endif  // ZLISP_LEXER_H
