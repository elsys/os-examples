#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE (1024 * 1024 * 1024)

unsigned char *data;

int average1() {
	int res;
	int i;
	long long int sum = 0;
	
	for (i = 0; i < (SIZE / 2); i++) {
		data[i] = i;
		sum += data[i];
	}
	res = sum / (SIZE / 2);
	
	return res;
}

int average2() {
	int res;
	int i;
	long long int sum = 0;
	
	for (i = (SIZE / 2); i < SIZE; i++) {
		data[i] = i;
		sum += data[i];
	}
	res = sum / (SIZE / 2);
	
	return res;
}

int main() {
	data = malloc(sizeof(char) * SIZE);
	memset(data, 0, SIZE);
	
	int pid = fork();
	if (pid == 0) {
		return average1(NULL);
	} else {
		int average2_res = average2(NULL);

		int status;
		wait(&status);
		
		int average1_res = WEXITSTATUS(status);
		
		printf("Average value: %d\n", (average1_res + average2_res) / 2);
	}

	free(data);

	return 0;
}
