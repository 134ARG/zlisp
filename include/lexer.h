//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_LEXER_H
#define ZLISP_LEXER_H

#include "context.h"
#include "string_utils.h"

enum status next_segment(struct file_context* ctx, string* segment);

#endif //ZLISP_LEXER_H
