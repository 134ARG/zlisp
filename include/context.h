//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_CONTEXT_H
#define ZLISP_CONTEXT_H

#include "char_utils.h"
#include "logger.h"
#include "status.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

struct file_context {
	FILE*  file;
	size_t lineno;
	size_t index;
};

static struct file_context
make_file_context(const char* filename, const char* mode)
{
	FILE* file = fopen(filename, mode);
	if (!file) {
		LOG_ERROR("Can not open file: %s\n", filename);
	}
	return (struct file_context){
	    .file   = file,
	    .lineno = 1,
	    .index  = 0,
	};
}

static void
clean_file_context(struct file_context* ctx)
{
	if (ctx->file) {
		fclose(ctx->file);
	}
	ctx->lineno = 0;
	ctx->index  = 0;
	ctx->file   = NULL;
}

static int
file_context_getchar(struct file_context* ctx)
{
	int next = fgetc(ctx->file);
	if (is_line_breaker(next)) {
		ctx->lineno++;
		ctx->index = 0;
	} else if (next != EOF) {
		ctx->index++;
	}
	return next;
}

static enum status
file_context_rollback(struct file_context* ctx, int offset)
{
	if (fseek(ctx->file, offset, SEEK_CUR) == -1) {
		return ERR_FILE_CURSOR;
	}
	return OK;
}

#endif  // ZLISP_CONTEXT_H
