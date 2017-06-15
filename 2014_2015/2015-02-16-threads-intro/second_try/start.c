#include <stdio.h>
#include <math.h>

#define SIZE 20000000

double array[SIZE];

int main() {
	int i;
	for(i = 0; i < SIZE; i++) {
		array[i] = - (i % 255);
	}

	for(i = 0; i < SIZE; i++) {
		array[i] = cos(array[i]);
	}

	long long sum = 0;
		

	printf("%f\n", array[5]);

	return 0;
}
