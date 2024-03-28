#ifndef __CC_STACK_H
#define __CC_STACK_H

#include "cc_array.h"
#include "cc_common.h"
#include <stddef.h>

struct cc_stack {
	struct cc_array *data;
	size_t top;
};

#ifndef NO_MALLOC
struct cc_stack *cc_stack_new(size_t elem_nums, size_t elem_size);
int cc_stack_delete(struct cc_stack *self);
#endif

int cc_stack_init(struct cc_stack *self, struct cc_array *data);

int cc_stack_push(struct cc_stack *self, void *item);
int cc_stack_pop(struct cc_stack *self, void *item);

#endif
