#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define ARRAY_SIZE 100000000
#define FALSE 0
#define TRUE 1

long double sum = 0;
int turn;
int flag[2] = {FALSE, FALSE};

void *sumfun1(void *p) {
	flag[0] = TRUE;
	turn = 1;
	while (flag[1] && turn == 1);
	int i;
	for(i = 0; i < ARRAY_SIZE/2; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	flag[0] = FALSE;
	return NULL;
}

void *sumfun2(void *p) {
	flag[1] = TRUE;
	turn = 0;
	while (flag[0] && turn == 0);
	int i;
	for(i = ARRAY_SIZE/2; i < ARRAY_SIZE; i++) {
		sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	flag[1] = FALSE;
	return NULL;
}

int main() {
	int i;
		
	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread1, NULL, sumfun1, NULL);
	pthread_create(&thread2, NULL, sumfun2, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("%Lf\n", sum);
}


//Expected result 6799999932
