#include "status.h"
#include "symbol.h"
#include "uthash/uthash.h"

struct table_entry {
	struct symbol _symbol;
	char*         _name;
	size_t        _id;

	UT_hash_handle hh_id;
	UT_hash_handle hh_name;
};

struct symbol_table {
	struct table_entry* symbols_by_id;
	struct table_entry* symbols_by_name;

	size_t size;
};

enum status symbol_table_name_get(struct symbol_table table,
                                  string              name,
                                  struct symbol**     item);

enum status symbol_table_id_get(struct symbol_table table,
                                size_t              id,
                                struct symbol**     item);

size_t symbol_table_add(struct symbol_table* table, struct symbol new);

void clean_symbol_table(struct symbol_table* table);