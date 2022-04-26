//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_STREAM_H
#define ZLISP_STREAM_H

#include "char_utils.h"
#include "logger.h"
#include "status.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

struct file_stream {
	FILE*  file;
	size_t lineno;
	size_t index;
};

static struct file_stream
make_file_stream(const char* filename, const char* mode)
{
	FILE* file = fopen(filename, mode);
	if (!file) {
		LOG_ERROR("Can not open file: %s\n", filename);
	}
	return (struct file_stream){
	    .file   = file,
	    .lineno = 1,
	    .index  = 0,
	};
}

static void
clean_file_stream(struct file_stream* ctx)
{
	if (ctx->file) {
		fclose(ctx->file);
	}
	ctx->lineno = 0;
	ctx->index  = 0;
	ctx->file   = NULL;
}

static int
file_stream_getchar(struct file_stream* ctx)
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
file_stream_rollback(struct file_stream* ctx, int offset)
{
	if (fseek(ctx->file, offset, SEEK_CUR) == -1) {
		return ERR_FILE_CURSOR;
	}
	return OK;
}

#endif  // ZLISP_STREAM_H
