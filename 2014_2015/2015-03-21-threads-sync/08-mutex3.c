#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define RANGE_END 100000000

pthread_mutex_t mutex;

int sum = 0;

void *thread_worker1(void *arg) {
	size_t i = 0;
	
	int local_sum = 0;
	
	for (i = 0; i < RANGE_END / 2; i++) {
		local_sum++;
	}
	
	pthread_mutex_lock(&mutex);
	sum += local_sum;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

void *thread_worker2(void *arg) {
	size_t i = 0;

	int local_sum = 0;
	
	for (i = RANGE_END / 2; i < RANGE_END; i++) {
		local_sum++;
	}
	
	pthread_mutex_lock(&mutex);
	sum += local_sum;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, thread_worker1, NULL);
	pthread_create(&thread2, NULL, thread_worker2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);

	printf("%d\n", sum);

	return 0;
}
