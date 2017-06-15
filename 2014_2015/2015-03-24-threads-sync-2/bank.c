#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

double bank_balance = 0.0;
double ivan_account = 0.0;
double petar_account = 0.0;

pthread_mutex_t lock;

void deposit(double amount, double *to) {
	pthread_mutex_lock(&lock);
	bank_balance += amount;
	pthread_mutex_unlock(&lock);
	*to += amount;
	
}

int withdraw(double amount, double *from) {
	pthread_mutex_lock(&lock);
	bank_balance -= amount;
	pthread_mutex_unlock(&lock);
	*from -= amount;
}

void *ivan(void *arg) {
	int i;
	for(i = 0; i < 1000000; i++) {
		if(rand() % 2 <= 1) {
			deposit(rand() % 10000, &ivan_account);
		}
		else {
			withdraw(rand() % 10000, &ivan_account);
		}

	}
}

void *petar(void *arg) {
	int i;
	for(i = 0; i < 1000000; i++) {
		if(rand() % 1000 <= 500) {
			deposit(rand() % 10000, &petar_account);
		}
		else {
			withdraw(rand() % 10000, &petar_account);
		}
	}
}

int main() {
	srand(time(NULL));
	
	pthread_t threads[2];

	pthread_mutex_init(&lock, NULL);
	pthread_create(&threads[0], NULL, ivan, NULL);
	pthread_create(&threads[1], NULL, petar, NULL);
	
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);


	printf("%f %f\n", ivan_account + petar_account, bank_balance);

	pthread_mutex_destroy(&lock);

	return 0;
}
