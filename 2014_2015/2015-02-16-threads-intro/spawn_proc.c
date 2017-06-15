#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	
	int i = 0;
	for (i = 0; i < 10000; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			printf("Hello world!\n");
			return 1;
		}
	}
	
	for (i = 0; i < 10000; i++) {
		wait(NULL);
	}
	
	return 0;
}
