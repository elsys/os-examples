#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define SLOTS 5


pthread_mutex_t table_mutex;
int table[SLOTS];
int mother_position = 0;
int ivancho_position = 0;


void *mother_thread(void *arg) {
	int count = 0;
	while(true) {
		pthread_mutex_lock(&table_mutex);
		if(((mother_position + 1) % SLOTS) != ivancho_position) {
			pthread_mutex_unlock(&table_mutex);
			printf("Ivancho's mother is preparing pastichka %d\n", count);
			sleep(1);
			
			pthread_mutex_lock(&table_mutex);
			table[mother_position] = count;
			mother_position = (mother_position + 1) % SLOTS;
			pthread_mutex_unlock(&table_mutex);
			count++;
		}
		else {
			pthread_mutex_unlock(&table_mutex);
			printf("Ivancho's mother is laundering\n");
			sleep(1);
		}
	}
}

void *ivancho_thread(void *arg) {
	int count;
	while(true) {
		pthread_mutex_lock(&table_mutex);
		if(ivancho_position != mother_position) {
			count = table[ivancho_position];
			ivancho_position = (ivancho_position + 1) % SLOTS;
			pthread_mutex_unlock(&table_mutex);
			
			printf("Ivancho is eating pastichka %d\n", count);
			sleep(3);
		}
		else {
			pthread_mutex_unlock(&table_mutex);
			printf("Ivancho is 'playing' with Mariika\n");
			sleep(3);
		}
	}
}

int main() {
	srand(time(NULL));
	pthread_mutex_init(&table_mutex, NULL);
	pthread_t threads[2];
	
	pthread_create(&threads[0], NULL, mother_thread, NULL);
	pthread_create(&threads[1], NULL, ivancho_thread, NULL);
	
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	
	pthread_mutex_destroy(&table_mutex);
}
