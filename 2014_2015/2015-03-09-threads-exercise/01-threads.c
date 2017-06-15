#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define ARRAY_SIZE 100000000

long double sum = 0;

void *check(void *arg) {
	for(i = 0; i < ARRAY_SIZE; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	return NULL;
}

int main() {

	pthread_t thread;
	pthread_create(&thread, NULL, check, NULL);
	
	pthread_join(thread, NULL);
	
	printf("%Lf\n", sum);
	
	return 0;
}


//Expected result 6799999932
