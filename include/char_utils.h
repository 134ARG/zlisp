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
is_symbol(int ch)
{
	return isalpha(ch) || is_underscore(ch) || is_score(ch) || isalnum(ch) ||
	       is_slash(ch);
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

#endif  // ZLISP_CHAR_UTILS_H
