//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_STRING_UTILS_H
#define ZLISP_STRING_UTILS_H

#include "status.h"
#include "check.h"
#include <stdlib.h>
#include <memory.h>

#define DEFAULT_CAPACITY 5

typedef struct string {
	size_t size;
	size_t capacity;
	char* data;
} string;

static inline string
string_new()
{
	return (string) {
			.size = 0, .capacity = DEFAULT_CAPACITY,
			.data = calloc(DEFAULT_CAPACITY + 1, sizeof(char)),
	};
}

static inline void
string_free(string* s)
{
	free(s->data);
	s->size = s->capacity = 0;
	s->data = NULL;
}

static inline enum status
string_clean(string* s)
{
	string_free(s);
	*s = string_new();
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
	string_expand(s, new_size); // check ok
	memcpy(&s->data[s->size], cstr, cstr_size);
	string_add_tail(s);
	return OK;
}

static inline enum status
string_append_str(string* s, const string tail)
{
	return string_append_cstr(s, tail.data, tail.size);
}


#endif //ZLISP_STRING_UTILS_H
