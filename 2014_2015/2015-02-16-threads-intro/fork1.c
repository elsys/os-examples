#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE (1024 * 1024 * 1024)

unsigned char *data;

int average() {
	int res;
	int i;
	long long int sum = 0;
	
	for (i = 0; i < SIZE; i++) {
		data[i] = i;
		sum += data[i];
	}
	res = sum / SIZE;
	
	return res;
}

int main() {
	data = malloc(sizeof(char) * SIZE);
	memset(data, 0, SIZE);

	printf("Average value: %d\n", average());

	free(data);

	return 0;
}
