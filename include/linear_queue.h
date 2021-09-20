
#include "status.h"
#include <stdlib.h>

#define CAPACITY_STEP 5

struct queue {
	void** data;
	size_t start;
	size_t end;
	size_t capacity;
};

struct queue make_queue();

enum status clean_queue(struct queue* q);

int is_queue_empty(const struct queue* q);
int is_queue_full(const struct queue* q);

enum status queue_push(struct queue* q, void* element);
enum status queue_get(struct queue* q, void** element);
enum status queue_reset(struct queue* q);