#include "unit_test.h"
#include <errno.h>
#include <stdio.h>

int
main()
{
	test_lexer();
	test_list();
	test_tables();
	test_queue();

	return 0;
}
