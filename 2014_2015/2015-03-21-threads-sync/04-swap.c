#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define RANGE_END 100000000

#define swap(ptr, val) atomic_exchange(ptr, val)

int sum = 0;

atomic_bool lock = 0;

void *thread_worker1(void *arg) {
	size_t i = 0;
	for (i = 0; i < RANGE_END / 2; i++) {
		
		int val = 1;
		while (val == 1) {
			val = swap(&lock, val);
		}
		
		sum++;
		
		atomic_flag_clear(&lock);
		
	}
	return NULL;
}

void *thread_worker2(void *arg) {
	size_t i = 0;
	
	for (i = RANGE_END / 2; i < RANGE_END; i++) {
		
		int val = 1;
		while (val == 1) {
			val = swap(&lock, val);
		}
		
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
