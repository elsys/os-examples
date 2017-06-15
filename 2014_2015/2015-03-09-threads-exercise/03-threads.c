#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000000

void *sumfun(void *p) {
	long double *sum = malloc(sizeof(long double));
	*sum = 0;
	
	int i;
	size_t start = (size_t) p;
	for(i = start; i < start + ARRAY_SIZE/2; i++) {
		*sum += sin(i) * sin(i) + cos(i) * cos(i);
	}
	
	return sum;
}

int main() {
	int i;
		
	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread1, NULL, sumfun, (void *) 0);
	pthread_create(&thread2, NULL, sumfun, (void *) (ARRAY_SIZE/2));
	
	long double sum = 0;
	long double *result;
	pthread_join(thread1, (void **) &result);
	sum += *result;
	free(result);
	
	pthread_join(thread2, (void **) &result);
	sum += *result;
	free(result);
	
	printf("%Lf\n", sum);
}


//Expected result 6799999932
