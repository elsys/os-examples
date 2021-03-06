#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define RANGE_END 100000000

#define testandset(ptr) (!atomic_flag_test_and_set(ptr))

int sum = 0;

atomic_flag lock = ATOMIC_FLAG_INIT;

void *thread_worker1(void *arg) {
	size_t i = 0;
	for (i = 0; i < RANGE_END / 2; i++) {
		
		while (!testandset(&lock));
		sum++;
		atomic_flag_clear(&lock);
		
	}
	return NULL;
}

void *thread_worker2(void *arg) {
	size_t i = 0;
	for (i = RANGE_END / 2; i < RANGE_END; i++) {
		
		while (!testandset(&lock));
		sum++;
		atomic_flag_clear(&lock);
		
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
