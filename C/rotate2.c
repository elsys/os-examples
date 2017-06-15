#include <stdio.h>

/*
 * swaps any two values - for more information see the 'swap' exercise on the site of the course
 * http://lubo.elsys-bg.org/operating_systems/2014-2015/
 */
void swap_any(void* pa, void* pb, int size) {
	int i;
	char c[4096];

	char *cpa = pa;
	char *cpb = pb;

	for (i = 0; i < size; i++) {
		c[i] = cpa[i];
	}

	for (i = 0; i < size; i++) {
		cpa[i] = cpb[i];
	}

	for (i = 0; i < size; i++) {
		cpb[i] = c[i];
	}

	// TODO: Think of a way to use only one for loop
}

/*
 * rotates an array of N elements of size S inplace - the first element becomes the last and
 * the last element becomes the first, the second element becomes the one before the
 * last and the one before the last element becomes the second, ..., the i-th element,
 * becomes the "(N - i)"-th and the "(N - i)"-th element becomes the i-th.
 *
 * i.e. after applying a rotate on the array {1, 2, 3, 4} the result must be {4, 3, 2, 1}
 *
 */
void rotate(void* parr, size_t num_elements, size_t element_size) {

	char *first_elem = parr; // calculate the address of the first element in the array
	char *last_elem = first_elem + ((num_elements - 1) * element_size); // calculate the address of the lat element in the array
	// we need the '-1' here, otherwise we will  ~~~^
	// point to the element _after_ the array end

	size_t i;
	// NOTE: we must loop (num_elements / 2) times otherwise we will rotate the array twice
	// and the result would be the original array!
	for (i = 0; i < num_elements / 2; i++) {
		// calculate the address of the i-th element
		void* current_front_element = first_elem + (i * element_size);
		// calculate the address of the (N - i)-th element
		void* current_back_element = last_elem - (i * element_size);

		// swap them
		swap_any(current_front_element, current_back_element, element_size);
	}
}

int main() {
	int z[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i = 0;

	for (i = 0; i < 10; i++) {
		printf("%d ", z[i]);
	}
	printf("\n");

	rotate(z, 10, sizeof(int));

	for (i = 0; i < 10; i++) {
		printf("%d ", z[i]);
	}
	printf("\n");

	return 0;
}
