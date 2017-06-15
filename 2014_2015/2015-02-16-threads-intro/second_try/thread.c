#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/wait.h>

#define SIZE 20000000

double array[SIZE];

void* arrCos(void* param) {
	int i;
	for(i = 0; i < SIZE/2; i++) {
		array[i] = cos(array[i]);
	}
	
	return NULL;
}

int main() {
	int i;
	for(i = 0; i < SIZE; i++) {
		array[i] = - (i % 255);
	}

	pthread_t thread;
	pthread_create(&thread, NULL, arrCos, NULL);


	for(i = SIZE/2; i < SIZE; i++) {
		array[i] = cos(array[i]);
	}
	
	pthread_join(thread, NULL);

	wait(NULL);
	
	printf("%f\n", array[5]);

	return 0;
}
