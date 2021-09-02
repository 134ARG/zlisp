//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_STRING_UTILS_H
#define ZLISP_STRING_UTILS_H

#include "check.h"
#include "status.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 5

#define STRING_ITER(string_name, char_ptr)                                     \
	for (char* char_ptr = (string_name).data;                                  \
	     char_ptr - (string_name).data < (string_name).size;                   \
	     ++char_ptr)

// C11 6.5.8 p.5
#define STRING_ITER_FROM(string_name, char_ptr, start)                         \
	if ((start) < (string_name).size)                                          \
		for (char* char_ptr = (string_name).data + (start);                    \
		     char_ptr - (string_name).data < (string_name).size;               \
		     ++char_ptr)

typedef struct string {
	size_t size;
	size_t capacity;
	char*  data;
} string;

static inline string
make_string()
{
	return (string){
	    .size     = 0,
	    .capacity = DEFAULT_CAPACITY,
	    .data     = calloc(DEFAULT_CAPACITY + 1, sizeof(char)),
	};
}

static inline string
make_string_from_cstr(const char* cstr)
{
	return (string){
	    .size     = strlen(cstr),
	    .capacity = strlen(cstr),
	    .data     = strdup(cstr),
	};
}

static inline enum status
clean_string(string* s)
{
	if (s->data) {
		free(s->data);
	}
	s->size     = 0;
	s->capacity = 0;
	s->data     = NULL;

	return OK;
}

static inline enum status
string_set_cstr(string* s, const char* new)
{
	clean_string(s);
	*s = make_string_from_cstr(new);
	return OK;
}

static inline enum status
string_set(string* s, string* new)
{
	CHECK_OK(string_set_cstr(s, new->data));
	return OK;
}

static inline enum status
string_reset(string* s)
{
	clean_string(s);
	*s = make_string();
	return OK;
}

static inline enum status
string_expand(string* s, size_t new_size)
{
	if (new_size > s->capacity) {
		char* new_data = reallocarray(s->data, new_size, sizeof(char));
		if (!new_data) {
			return ERR_NO_MEM;
		}
		s->data = new_data;
	}
	return OK;
}

static inline void
string_add_tail(string* s)
{
	s->data[s->size] = '\0';
}

static inline enum status
string_push(string* s, char ch)
{
	if (s->size == s->capacity) {
		CHECK_OK(string_expand(s, s->capacity * 2 + 1));
		s->capacity = s->capacity * 2;
	}

	s->data[s->size++] = ch;
	string_add_tail(s);

	return OK;
}

static inline enum status
string_append_cstr(string* s, const char* cstr, size_t cstr_size)
{
	size_t new_size = s->size + cstr_size;
	string_expand(s, new_size);  // check ok
	memcpy(&s->data[s->size], cstr, cstr_size);
	string_add_tail(s);
	return OK;
}

static inline enum status
string_append_str(string* s, const string tail)
{
	return string_append_cstr(s, tail.data, tail.size);
}

static inline int
string_compare(const string s1, const string s2)
{
	return strcmp(s1.data, s2.data);
}

static inline int
string_compare_cstr(const string s1, const char* s2)
{
	return strcmp(s1.data, s2);
}

#endif  // ZLISP_STRING_UTILS_H
