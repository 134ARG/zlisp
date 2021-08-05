#include "tables.h"
#include "status.h"
#include "string_utils.h"
#include "symbol.h"
#include "uthash/uthash.h"
#include <stdlib.h>

enum status
symbol_table_name_get(struct symbol_table table,
                      string              name,
                      struct symbol**     item)
{
	struct table_entry* target = NULL;
	HASH_FIND(hh_name, table.symbols_by_name, name.data, name.size, target);
	if (target) {
		*item = &target->_symbol;
		return OK;
	}

	*item = NULL;
	return INFO_OBJ_NOT_FOUND;
}

enum status
symbol_table_id_get(struct symbol_table table, size_t id, struct symbol** item)
{
	struct table_entry* target = NULL;
	HASH_FIND(hh_id, table.symbols_by_id, &id, sizeof(id), target);
	if (target) {
		*item = &(target->_symbol);
		return OK;
	}

	*item = NULL;
	return INFO_OBJ_NOT_FOUND;
}

size_t
symbol_table_add(struct symbol_table* table, struct symbol new)
{
	struct table_entry* new_entry = malloc(sizeof(struct table_entry));

	new_entry->_symbol = new;
	new_entry->_name   = new.name.data;
	new_entry->_id     = table->size;

	HASH_ADD_KEYPTR(hh_name,
	                table->symbols_by_name,
	                new_entry->_name,
	                new_entry->_symbol.name.size,
	                new_entry);

	HASH_ADD(hh_id, table->symbols_by_id, _id, sizeof(size_t), new_entry);
	table->size++;

	return table->size - 1;
}

void
clean_symbol_table(struct symbol_table* table)
{
	if (table) {
		struct table_entry* current;
		struct table_entry* tmp;
		HASH_ITER (hh_id, table->symbols_by_id, current, tmp) {
			clean_string(&current->_symbol.name);
			free(current);
		}
		HASH_CLEAR(hh_id, table->symbols_by_id);
	}
}