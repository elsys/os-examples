#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define SIZE 20000000

double array[SIZE];

int main() {
	int i;
	for(i = 0; i < SIZE; i++) {
		array[i] = - (i % 255);
	}

	pid_t pid = fork();

	if(pid == 0) {

		for(i = 0; i < SIZE/2; i++) {
			array[i] = cos(array[i]);
		}
	}
	else {

		for(i = SIZE/2; i < SIZE; i++) {
			array[i] = cos(array[i]);
		}


		wait(NULL);
		
		printf("%f\n", array[5]);

	}
	return 0;
}
