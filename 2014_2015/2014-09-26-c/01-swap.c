#include <stdio.h>

/*
 * naive swap function
 * 
 *   ** TODO: make it work **
 * 
*/
void swap(int a, int b) {
	int c = a;
	a = b;
	b = c;
}

int main() {
	
	int a = 5;
	int b = 10;

	// does not work (why ?)
	swap(a, b);

	printf("a: %d b: %d\n", a, b);
	
	return 0; // return exit code to the calling program
}
