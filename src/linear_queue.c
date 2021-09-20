#include "linear_queue.h"
#include "check.h"
#include "status.h"
#include <memory.h>
#include <stdlib.h>

struct queue
make_queue()
{
	return (struct queue){
	    .data     = malloc(CAPACITY_STEP * sizeof(void*)),
	    .start    = 0,
	    .end      = 0,
	    .capacity = CAPACITY_STEP,
	};
}

enum status
clean_queue(struct queue* q)
{
	if (q->data) {
		free(q->data);
	}
	q->start    = 0;
	q->end      = 0;
	q->data     = NULL;
	q->capacity = 0;
	return OK;
}

int
is_queue_empty(const struct queue* q)
{
	return q->start == q->end;
}

int
is_queue_full(const struct queue* q)
{
	return (q->end + 1) % q->capacity == q->start;
}

enum status
extend_queue(struct queue* q, size_t new_capacity)
{
	void** new = reallocarray(q->data, new_capacity, sizeof(void*));
	if (new) {
		if (q->start > q->end) {
			size_t length    = q->capacity - q->start;
			size_t new_start = new_capacity - length;
			memmove(&new[new_capacity - length], &q->data[q->start], length);
			q->data     = new;
			q->start    = new_start;
			q->capacity = new_capacity;
		}
		return OK;
	} else {
		return ERR_NO_MEM;
	}
}

enum status
queue_push(struct queue* q, void* element)
{
	if (is_queue_full(q)) {
		CHECK_OK(extend_queue(q, q->capacity + CAPACITY_STEP));
	}
	q->data[q->end] = element;
	q->end          = (q->end + 1) % q->capacity;
	return OK;
}

enum status
queue_get(struct queue* q, void** element)
{
	if (is_queue_empty(q)) {
		*element = NULL;
		return ERR_CONTAINER_EMPTY;
	}
	*element = q->data[q->start];
	q->start = (q->start + 1) % q->capacity;
	return OK;
}

enum status
queue_reset(struct queue* q)
{
	CHECK_OK(clean_queue(q));
	*q = make_queue();
	return OK;
}
