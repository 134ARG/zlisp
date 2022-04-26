#ifndef ZLISP_READER_H
#define ZLISP_READER_H

#include "char_utils.h"
#include "context.h"
#include "lexer.h"
#include "status.h"
#include "stream.h"
#include "symbol.h"

enum status reader(struct file_stream* s,
                   struct symbol**     sym_ptr,
                   struct context*     ctx);

#endif  // ZLISP_READER_H
