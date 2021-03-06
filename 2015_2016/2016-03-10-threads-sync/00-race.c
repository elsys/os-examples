#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define ARRAY_SIZE 10000000

long double sum = 0;

/* THREAD 1 */
void *sumfun1(void *p) {
	int i;
	for(i = 0; i < ARRAY_SIZE/2; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	return NULL;
}

/* THREAD 2 */
void *sumfun2(void *p) {
	int i;
	for(i = ARRAY_SIZE/2; i < ARRAY_SIZE; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	return NULL;
}


int main(int argc, char **argv) {
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, sumfun1, NULL);
	pthread_create(&thread2, NULL, sumfun2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("%Lf\n", sum);

	return 0;
}
