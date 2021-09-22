
#include "check.h"
#include "status.h"
#include <memory.h>
#include <stdlib.h>

#define CAPACITY_STEP 5

#define INITIALIZE_QUEUE(QUEUE, T)                                             \
	struct QUEUE {                                                             \
		T*     data;                                                           \
		size_t start;                                                          \
		size_t end;                                                            \
		size_t capacity;                                                       \
	};                                                                         \
                                                                               \
	static inline struct QUEUE make_##QUEUE() {                                \
		return (struct QUEUE){                                                 \
		    .data     = malloc(CAPACITY_STEP * sizeof(void*)),                 \
		    .start    = 0,                                                     \
		    .end      = 0,                                                     \
		    .capacity = CAPACITY_STEP,                                         \
		};                                                                     \
	}                                                                          \
                                                                               \
	static inline enum status clean_##QUEUE(struct QUEUE* q)                   \
	{                                                                          \
		if (q->data) {                                                         \
			free(q->data);                                                     \
		}                                                                      \
		q->start    = 0;                                                       \
		q->end      = 0;                                                       \
		q->data     = NULL;                                                    \
		q->capacity = 0;                                                       \
		return OK;                                                             \
	}                                                                          \
                                                                               \
	static inline int is_##QUEUE##_empty(const struct QUEUE* q)                \
	{                                                                          \
		return q->start == q->end;                                             \
	}                                                                          \
                                                                               \
	static inline int is_##QUEUE##_full(const struct QUEUE* q)                 \
	{                                                                          \
		return (q->end + 1) % q->capacity == q->start;                         \
	}                                                                          \
                                                                               \
	static inline enum status extend_##QUEUE(struct QUEUE* q,                  \
	                                         size_t        new_capacity)       \
	{                                                                          \
		T* new = reallocarray(q->data, new_capacity, sizeof(T));               \
		if (new) {                                                             \
			if (q->start > q->end) {                                           \
				size_t length    = q->capacity - q->start;                     \
				size_t new_start = new_capacity - length;                      \
				memmove(&new[new_capacity - length],                           \
				        &q->data[q->start],                                    \
				        length);                                               \
				q->data     = new;                                             \
				q->start    = new_start;                                       \
				q->capacity = new_capacity;                                    \
			}                                                                  \
			return OK;                                                         \
		} else {                                                               \
			return ERR_NO_MEM;                                                 \
		}                                                                      \
	}                                                                          \
                                                                               \
	static inline enum status QUEUE##_push(struct QUEUE* q, T element)         \
	{                                                                          \
		if (is_##QUEUE##_full(q)) {                                            \
			CHECK_OK(extend_##QUEUE(q, q->capacity + CAPACITY_STEP));          \
		}                                                                      \
		q->data[q->end] = element;                                             \
		q->end          = (q->end + 1) % q->capacity;                          \
		return OK;                                                             \
	}                                                                          \
                                                                               \
	static inline enum status QUEUE##_get(struct QUEUE* q, T* element)         \
	{                                                                          \
		if (is_##QUEUE##_empty(q)) {                                           \
			return ERR_CONTAINER_EMPTY;                                        \
		}                                                                      \
		*element = q->data[q->start];                                          \
		q->start = (q->start + 1) % q->capacity;                               \
		return OK;                                                             \
	}                                                                          \
                                                                               \
	static inline enum status QUEUE##_reset(struct QUEUE* q)                   \
	{                                                                          \
		CHECK_OK(clean_##QUEUE(q));                                            \
		*q = make_##QUEUE();                                                   \
		return OK;                                                             \
	}
