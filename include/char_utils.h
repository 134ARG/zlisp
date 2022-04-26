//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_CHAR_UTILS_H
#define ZLISP_CHAR_UTILS_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int
is_lparen(int ch)
{
	return ch == '(';
}

enum syntax_type {
	CONSTITUENT,
	TERMINATING_MACRO_CHAR,
	NON_TERMINATING_MACRO_CHAR,
	WHITESPACE,
	SINGLE_ESCAPE,
	MULTIPLE_ESCAPE,
};

enum constituent_traits {
	INVALID,
	ALPHABETIC,
	ALPHADIGIT,
	PACKAGE_MARKER,
	PLUS_SIGN,
	MINUS_SIGN,
	DOT,
	DECIMAL_POINT,
	RATIO_MARKER,
	DOUBLE_EXPONENT_MARKER,
	FLOAT_EXPONENT_MARKER,
	SINGLE_EXPONENT_MARKER,
	LONG_EXPONENT_MARKER,
	SHORT_EXPONENT_MARKER,
};

static int
is_slash(int ch)
{
	return ch == '\\';
}

static int
is_doublequote(int ch)
{
	return ch == '"';
}

static int
is_dot(int ch)
{
	return ch == '.';
}

static int
is_rparen(int ch)
{
	return ch == ')';
}

static int
is_colon(int ch)
{
	return ch == ':';
}

static int
is_semi(int ch)
{
	return ch == ';';
}

static int
is_bar(int ch)
{
	return ch == '|';
}

static int
is_underscore(int ch)
{
	return ch == '_';
}

static int
is_score(int ch)
{
	return ch == '-';
}

static int
is_exponent(int ch)
{
	return ch == 'e' || ch == 'E';
}

static int
is_sign(int ch)
{
	return ch == '-' || ch == '+';
}

static int
is_line_breaker(int ch)
{
	return ch == '\n';
}

static int
is_blank(int ch)
{
	return isblank(ch) || iscntrl(ch) || is_line_breaker(ch);
}

static int
is_blank_or_eof(int ch)
{
	return is_blank(ch) || ch == EOF;
}

static int
is_symbol(int ch)
{
	return isalnum(ch) || is_underscore(ch) || is_score(ch) || is_slash(ch) ||
	       is_sign(ch);
}

static int
is_number_start(int ch)
{
	return is_sign(ch) || isdigit(ch);
}

static int
is_number(int ch)
{
	return is_sign(ch) || isdigit(ch) || is_exponent(ch) || is_dot(ch);
}

static int
any_but_eof_and_blank(int ch)
{
	return !is_blank_or_eof(ch);
}

#endif  // ZLISP_CHAR_UTILS_H
