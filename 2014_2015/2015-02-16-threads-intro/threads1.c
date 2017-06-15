#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

#define SIZE (1024 * 1024 * 1024)

unsigned char *data;

int average1_res;
int average2_res;

void *average1(void *p) {
	int i;
	long long int sum = 0;
	
	for (i = 0; i < (SIZE / 2); i++) {
		data[i] = i;
		sum += data[i];
	}
	average1_res = sum / (SIZE / 2);
	
	return NULL;
}

void* average2(void *p) {
	int i;
	long long int sum = 0;
	
	for (i = (SIZE / 2); i < SIZE; i++) {
		data[i] = i;
		sum += data[i];
	}
	average2_res = sum / (SIZE / 2);
	
	return NULL;
}

int main() {
	data = malloc(sizeof(char) * SIZE);
	memset(data, 0, SIZE);
	
	pthread_t thread;

	pthread_create(&thread, NULL, average1, NULL);
	
	average2(NULL);

	pthread_join(thread, NULL);

	printf("Average value: %d\n", (average1_res + average2_res) / 2);

	free(data);

	return 0;
}
