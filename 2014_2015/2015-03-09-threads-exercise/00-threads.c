#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define ARRAY_SIZE 100000000

long double sum = 0;

int main() {
	int i;
	
	for(i = 0; i < ARRAY_SIZE; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}

	printf("%Lf\n", sum);
}
