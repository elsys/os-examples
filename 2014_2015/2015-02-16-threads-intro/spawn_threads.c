#include <stdio.h>
#include <pthread.h>

void *hello(void *p) {
	printf("Hello world!\n");
	return NULL;
}

int main() {
	pthread_t threads[10000];
	
	int i;
	for (i = 0; i < 10000; i++) {
		pthread_create(&threads[i], NULL, hello, NULL);
	}
	for (i = 0; i < 10000; i++) {
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}
