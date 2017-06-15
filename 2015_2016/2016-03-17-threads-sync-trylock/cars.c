#include <pthread.h>
#include <stdio.h>

pthread_mutex_t cars[3];


void *renter(void *arg) {
	int id = (int) arg;
	while (1) {
		int i;
		for (i = 0; i < 3; i++) {
			if (pthread_mutex_trylock(&cars[i]) == 0) {
				printf("Driver %d driving car %d\n", id, i);
				sleep(1);
				pthread_mutex_unlock(&cars[i]);
				break;
			}
		}
		sleep(1);
	}
}

int main() {
	pthread_t renters[5];
	int i;
	for (i = 0; i < 3; i++) {
		pthread_mutex_init(&cars[i], NULL);
	}
	
	for (i = 0; i < 5; i++) {
		pthread_create(&renters[i], NULL, renter, (void *) i);
	}
	
	for (i = 0; i < 5; i++) {
		pthread_join(renters[i], NULL);
	}
	
	for (i = 0; i < 3; i++) {
		pthread_mutex_destroy(&cars[i]);
	}
}
