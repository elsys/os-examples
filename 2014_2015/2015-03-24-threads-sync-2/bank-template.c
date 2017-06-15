#include <time.h>
#include <stdlib.h>


double bank_balance = 0.0;
double ivan_account = 0.0;
double petar_account = 0.0;


void deposit(double amount, double *to) {
	// Adds amount to account *to
	// Adds amount to total bank balance
}

int withdraw(double amount, double *from) {
	// Removes amount from account *from
	// Removes amount from total bank balance

}

// Account holder actions
	for(i = 0; i < 1000000; i++) {
		if(rand() % 2 <= 1) {
			deposit(rand() % 10000, &ivan_account);
		}
		else {
			withdraw(rand() % 10000, &ivan_account);
		}
	}


int main() {
	srand(time(NULL));

	// Something very clever

	printf("%f %f\n", ivan_account + petar_account, bank_balance);

	return 0;
}
