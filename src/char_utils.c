#include "char_utils.h"
#include "string_utils.h"

static enum status
load_syntax_type(struct string_vector* v)
{
	CHECK_OK(resize_string_vector(v, syntax_type_size));

	CHECK_OK(string_vector_set(v,
	                           CONSTITUENT,
	                           make_string_from_cstr(
	                               "!$%&*+-./0123456789:<=>?@[]^_{}~\b"
	                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	                               "abcdefghigklmnopqrstuvwxyz")));
	CHECK_OK(string_vector_set(v,
	                           TERMINATING_MACRO_CHAR,
	                           make_string_from_cstr("\"'(),;`")));
	CHECK_OK(string_vector_set(v,
	                           NON_TERMINATING_MACRO_CHAR,
	                           make_string_from_cstr("#")));
	CHECK_OK(
	    string_vector_set(v, WHITESPACE, make_string_from_cstr("\t\n\v\f\r ")));
	CHECK_OK(string_vector_set(v, SINGLE_ESCAPE, make_string_from_cstr("\\")));
	CHECK_OK(string_vector_set(v, MULTIPLE_ESCAPE, make_string_from_cstr("|")));

	return OK;
}

static enum status
load_trait(struct string_vector* v)
{
	CHECK_OK(resize_string_vector(v, trait_size));

	CHECK_OK(
	    string_vector_set(v, INVALID, make_string_from_cstr("\b\t\n\v\f\r ")));
	CHECK_OK(string_vector_set(v,
	                           ALPHABETIC,
	                           make_string_from_cstr(
	                               "!\"#$%&'()*,;<=>?@[\\]^_`|~{}+-./")));
	CHECK_OK(
	    string_vector_set(v,
	                      ALPHADIGIT,
	                      make_string_from_cstr("0123456789"
	                                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	                                            "abcdefghigklmnopqrstuvwxyz")));
	CHECK_OK(string_vector_set(v, PACKAGE_MARKER, make_string_from_cstr(":")));
	CHECK_OK(string_vector_set(v, PLUS_SIGN, make_string_from_cstr("+")));
	CHECK_OK(string_vector_set(v, MINUS_SIGN, make_string_from_cstr("-")));
	CHECK_OK(string_vector_set(v, DOT, make_string_from_cstr(".")));
	CHECK_OK(string_vector_set(v, DECIMAL_POINT, make_string_from_cstr(".")));
	CHECK_OK(string_vector_set(v, RATIO_MARKER, make_string_from_cstr("/")));
	CHECK_OK(string_vector_set(v,
	                           DOUBLE_EXPONENT_MARKER,
	                           make_string_from_cstr("Dd")));
	CHECK_OK(string_vector_set(v,
	                           FLOAT_EXPONENT_MARKER,
	                           make_string_from_cstr("Ee")));
	CHECK_OK(string_vector_set(v,
	                           SINGLE_EXPONENT_MARKER,
	                           make_string_from_cstr("Ff")));
	CHECK_OK(string_vector_set(v,
	                           LONG_EXPONENT_MARKER,
	                           make_string_from_cstr("Ll")));
	CHECK_OK(string_vector_set(v,
	                           SHORT_EXPONENT_MARKER,
	                           make_string_from_cstr("Ss")));

	return OK;
}

enum status
load_readtable(struct readtable* rt)
{
	if (!rt) {
		return ERR_NULL_PTR;
	}

	CHECK_OK(load_syntax_type(&rt->synatx_types));
	CHECK_OK(load_trait(&rt->constituent_traits));

	return OK;
}

int
check_syntax_type(struct readtable* rt, enum syntax_type type, char x)
{
	struct string ptr;
	string_vector_get(&rt->synatx_types, type, &ptr);
	if (string_find_char(ptr, x, 0) != NPOS) {
		return 1;
	} else {
		return 0;
	}
}

int
check_trait_type(struct readtable* rt, enum constituent_trait type, char x)
{
	struct string* ptr;
	string_vector_get(&rt->constituent_traits, type, ptr);
	if (ptr && string_find_char(*ptr, x, 0) != NPOS) {
		return 1;
	} else {
		return 0;
	}
}
