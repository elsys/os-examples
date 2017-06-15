#include <stdio.h>

/* glossary:
 * 
 *   - 'identifier' - a name for an entity in C (a variable, a function, a type, etc)
 * 
 *   - 'element of a type', 'element' - in C: N logically grouped bytes of memory. N is determined by 
 *   the type of the element (i.e. if the type is int => N == sizeof(int) == 4 on 32bit CPU architectures)
 * 
 *   - 'variable' - an element of a type with an identifier. The identifier can be used directly to retrieve
 *   the value of an element and/or modify it.
 * 
 *   - 'address of an element', 'address' - the address in memory of the first byte occupied by an element. In C
 *   we can obtain the address of an element by prefixing it with '&' (ampersand) - i.e. '&a', '&c[10]'
 * 
 *   - 'pointer' - a special type of element which can only hold addresses to memory. Since all variables,
 *   functions, etc (any data) reside in memory, pointers can be used to modify and retrieve them
 *   via their addresses in memory. It is said that a pointer 'points to' (or 'refers to') a variable, function,
 *   element of a type, etc. via the stored address in the pointer, hence the name. An analogy could be made
 *   with page numbers and actual pages in a book. A page resides in a book and has an address - its page number.
 *   The page number indicates which page we are interested in without actually having to turn the book to that
 *   page, but if we need the actual information on the page, we can use its page number to find it in the 
 *   book and read it.
 * 
 *   - 'type of a pointer', 'pointer type' - indicates the type of elements a pointer can point to. Although a pointer
 *   always holds an address to memory, one pointer can point to a variable of type int, and another pointer can point
 *   to a variable of type double. In the first case when trying to get the contents of the int variable, the compiler
 *   has to read 4 bytes of data starting from the address stored in the pointer (on 32 bit CPU architectures). In the
 *   second case the compiler has to read 8 bytes of data (on 32 bit CPU architectures). Hence, the reason for pointer
 *   types to exist is because the compiler is not smart enough to find out which pointer points to what automatically
 *   (and often there is no way for it to know even if it was infinitely smart).
 *   Returning to the book analogy, a more accurate example for addresses would be not with page numbers but with
 *   letter numbers starting from the begining of a book (i.e. 5 would mean the fifth letter from the book, 12344 would
 *   mean the 12344-th letter and so on). When a friend of yours tells you 'Check out 1432! It's hilarious!' and the 1432
 *   letter for example turns out to be the begining of the paragraph what does she mean exactly ? The whole paragraph ?
 *   The sentence ? To avoid ambiguity your friend must say explicitly what she means - 'Check out the *word* at 1432!
 *   It's hilarious!'
 * 
 *   - 'pointer arithmetic' - manipulating *pointers* (and respectively the addresses they store) via arithmetic operations.
 *   (i.e in C - 'p + N', where N is an integer, means 'offset a pointer by N *elements*')
 * 
 *   - 'to dereference a pointer' - to get a temporary identifier to a pointer's 'pointed to' element. The temporary
 *   identifier can then be used to retrieve and/or modify the element. In C this operation is achieved by using '*' in front
 *   of a pointer (or pointer arithmetic expression) - i.e. '*a', '*(a + 1)', '*(a - 3)'
 * 
 *   - 'void pointer' - a pointer that is not known to what type of element it points to - thus it cannot be dereferenced
 * 
 */

/*
 * swap integers
 */
void swap(int* pa, int* pb) {
	int c = *pa;
	*pa = *pb;
	*pb = c;
}

/*
 * swap floats
 */
void swap_floats(float* pa, float* pb) {
	float c = *pa;
	*pa = *pb;
	*pb = c;
}

/*
 * swap doubles
 */
void swap_doubles(double* pa, double* pb) {
	double c = *pa;
	*pa = *pb;
	*pb = c;
}

/*
 * swap chars
 */
void swap_chars(char* pa, char* pb) {
	char c = *pa;
	*pa = *pb;
	*pb = c;
}

/*
 * (more swap functions for all C types...)
 * 
 *   TODO: Is there a better way of swapping without creating
 *   almost identical code for every existing C type?
 */

int main() {
	
	int a = 5;
	int b = 10;

	float c = 3;
	float d = 11;

	// having separate function for every C type works, but requires too much typing
	swap(&a, &b);
	swap_floats(&c, &d);

	printf("a: %d b: %d\n", a, b);
	printf("c: %f d: %f\n", c, d);
	
	return 0; // return exit code to the calling program
}
