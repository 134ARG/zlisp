//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_LEXER_H
#define ZLISP_LEXER_H

#include "context.h"
#include "string_utils.h"

enum token_type {
	BAD_TOEKN,  // mal-formatted segment

	LPARAN,  // (
	RPARAN,  // )

	COMMA,        // ,
	COLON,        // :
	SEMICOLON,    // ;
	QUOTE,        // '
	DOUBLEQUOTE,  // "
	BACKQUOTE,    // `

	SYMBOL,  // symbol
	STRING,  // "something like that"
	NUMBER,  // 123.4 or 1234 or 123e3
};

struct token {
	enum token_type type;
	string          content;
};

enum status next_segment(struct file_context* ctx, string* segment);
enum status next_token(struct file_context* ctx, struct token* token);

#endif  // ZLISP_LEXER_H
