#include <stdio.h>

int main() {
	
	int a = 5;
	int b = 10;
	
	/*
	 * swap two integer variables
	 */
	int c = a;
	a = b;
	b = c;
	// TODO: make a function for swapping integers
	
	printf("a: %d b: %d\n", a, b);
	
	return 0; // return exit code to the calling program
}
