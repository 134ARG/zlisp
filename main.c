#include <stdio.h>
#include <errno.h>
#include "context.h"
#include "lexer.h"
#include "string_utils.h"

int
main()
{
	struct file_context test_file = file_context_new("./test.file", "r");
	if (!test_file.file) {
		printf("Hello, World!\n");
		return 0;
	}
	string segment = read_segment(&test_file);
	while (segment.size != 0) {
		fprintf(stderr, "%s, ", segment.data);
		string_clean(&segment);
		segment = read_segment(&test_file);
	}

	return 0;
}
