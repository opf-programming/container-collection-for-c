#include "cc_array.h"
#include "cc_common.h"
#include <assert.h>
#include <stdint.h>

int main() {
	struct cc_array array;
	struct cc_array_iter iter;
	uint8_t buffer[10 * sizeof(float)];

	float i;
	float tmp;
	float *iter_tmp;

	cc_array_init(&array, buffer, 10, sizeof(float));

	for (i = 0; i < 10; i++)
		assert(cc_array_set(&array, i, &i));

	for (i = 0; i < 10; i++) {
		assert(cc_array_get(&array, i, &tmp));
		assert(tmp == i);
	}

	cc_array_iter_init(&iter, &array);
	while (cc_iter_next(&iter, &iter_tmp))
		cc_debug_print("%.2f ", *iter_tmp);

	cc_debug_print("\n");

	return 0;
}
