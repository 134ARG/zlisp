//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_CONTEXT_H
#define ZLISP_CONTEXT_H

#include "char_utils.h"
#include "status.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct file_context {
    FILE* file;
    size_t lineno;
    size_t index;
};

static struct file_context
file_context_new(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (!file) {
        printf("Null pointer: %s\n", filename);
    }
    return (struct file_context) {
        .file = fopen(filename, mode),
        .lineno = 1,
        .index = 0,
    };
}

static void
file_context_free(struct file_context* ctx) {
    fclose(ctx->file);
    ctx->lineno = 0;
    ctx->index = 0;
}

static int
file_context_getchar(struct file_context* ctx) {
    int next = fgetc(ctx->file);
    if (is_line_breaker(next)) {
        ctx->lineno++;
        ctx->index = 0;
    } else if (next != EOF) {
        ctx->index++;
    }
    return next;
}

static int
file_context_rollback(struct file_context* ctx, int offset) {
    if (!fseek(ctx->file, offset, SEEK_CUR)) {
        return ERR_FILE_CURSOR;
    }
}

#endif //ZLISP_CONTEXT_H
