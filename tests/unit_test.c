//
// Created by fort64 on 7/9/2021.
//

#include "status.h"
#include "context.h"
#include "string_utils.h"
#include "lexer.h"
#include <stdio.h>

enum status
test_lexer()
{
	struct file_context test_file = file_context_new("/home/xen134/zlisp/cmake-build-debug/test.file", "r");
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

}
