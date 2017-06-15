#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define RANGE_END 100000000

int sum = 0;

atomic_int turn = 0;

void *thread_worker1(void *arg) {
	size_t i = 0;
	for (i = 0; i < RANGE_END / 2; i++) {
		
		while (turn == 1);
		sum++;
		turn = 1;
		
	}
	return NULL;
}

void *thread_worker2(void *arg) {
	size_t i = 0;
	for (i = RANGE_END / 2; i < RANGE_END; i++) {
		
		while (turn == 0);
		sum++;
		turn = 0;

	}
	return NULL;
}

int main(int argc, char **argv) {
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, thread_worker1, NULL);
	pthread_create(&thread2, NULL, thread_worker2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("%d\n", sum);

	return 0;
}
