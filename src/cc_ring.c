#include "cc_ring.h"
#include "cc_array.h"
#include <stdio.h>
#include <stdlib.h>

static inline size_t _next_index(struct cc_ring *self, size_t index) {
	size_t next_index = index + 1;
	if (cc_array_check(self->data, next_index))
		return next_index;
	else
		return 0;
}

static inline void debug_state(struct cc_ring *self) {
	printf("write_index: %zu, read_index %zu\n", self->write_index, self->read_index);
}

int cc_ring_put(struct cc_ring *self, void *item) {
	size_t write_index_next;

	write_index_next = _next_index(self, self->write_index);
	if (write_index_next == self->read_index)
		return 0;

	cc_array_set(self->data, self->write_index, item);
	self->write_index = write_index_next;

	return 1;
}

int cc_ring_get(struct cc_ring *self, void *item) {
	if (self->read_index == self->write_index)
		return 0;

	cc_array_get(self->data, self->read_index, item);
	self->read_index = _next_index(self, self->read_index);

	return 1;
}

void cc_ring_init(struct cc_ring *self, struct cc_array *data) {
	self->data = data;
	self->read_index = 0;
	self->write_index = 0;
}

#ifndef NO_MALLOC

struct cc_ring *cc_ring_new(size_t elem_nums, size_t elem_size) {
	struct cc_ring *self;
	struct cc_array *data;

	self = malloc(sizeof(*self));
	if (self == NULL)
		return NULL;

	/// 1 element will be wasted, so pass `elem_nums + 1` to `cc_array_new`.
	data = cc_array_new(elem_nums + 1, elem_size);
	if (data == NULL)
		return NULL;

	cc_ring_init(self, data);

	return self;
}

void cc_ring_delete(struct cc_ring *self) {
	cc_array_delete(self->data);
	free(self);
}

#endif
