#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define RANGE_END 100000000

int sum = 0;

atomic_int turn = 0;
atomic_int flags[2] = {0, 0};

void *thread_worker1(void *arg) {
	size_t i = 0;
	for (i = 0; i < RANGE_END / 2; i++) {
		
		atomic_store(&flags[0], 1);
		atomic_store(&turn, 1);
		while ((atomic_load(&flags[1]) == 1) && (atomic_load(&turn) == 1));
		sum++;
		atomic_store(&flags[0], 0);
		
	}
	return NULL;
}

void *thread_worker2(void *arg) {
	size_t i = 0;
	for (i = RANGE_END / 2; i < RANGE_END; i++) {

		atomic_store(&flags[1], 1);
		atomic_store(&turn, 0);
		while ((atomic_load(&flags[0]) == 1) && (atomic_load(&turn) == 0));
		sum++;
		atomic_store(&flags[1], 0);
		
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
