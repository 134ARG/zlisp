#include "context.h"
#include "lexer.h"

enum status
parse(struct file_context* ctx)
{
	struct token token = make_token();

	while(next_token(ctx, &token) == OK) {
		
	}
}