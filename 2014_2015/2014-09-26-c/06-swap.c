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
 * swap any type of variables!
 * 
 *   arg: size - holds the number of bytes the element pointed to by 'a' (or 'b') is occupying
 */
void swap_any(void* pa, void* pb, int size) {
	int i;
	char c[4096];
	
	/*
	 * IDEA: to support any type of variables we must swap all the bytes 
	 * occupied by the two variables
	 */
	
	/*
	 * To achieve cleaner code we try to minimize the casting to char pointer needed for
	 * the void pointer 'pa' by introducing a temporary char pointer variable and point it to
	 * the same address as 'pa' (in other words we make a "permament cast" to char pointer for 'pa' by
	 * using 'cpa')
	 */
	char *cpa = pa;
	// we can do the same for 'pb' as well
	char *cpb = pb;
	
	/*
	 * We can further reduce the noise in the syntax by recalling the fact that in C the square brackets are
	 * a shorthand way of simultaneously offsetting and dereferencing a pointer. Thus the following expressions
	 * are equivalent:
	 * 
	 *   *(pa + 1) <=> pa[1]
	 *         *pa <=> pa[0]
	 *   *(pa + k) <=> pa[k]
	 *   *(pa - 7) <=> pa[-7]
	 * 
	 */
	
	// c = *pa
	for (i = 0; i < size; i++) {
		// c[i] = *((char *)pa + i); // original
		// c[i] = *(cpa + i);        // with char pointer variables
		c[i] = cpa[i];               // with char pointer variables and square brackets
	}
	
	// *pa = *pb
	for (i = 0; i < size; i++) {
		// *((char *)pa + i) = *((char *)pb + i); // original
		// *(cpa + i) = *(cpb + i);               // with char pointer variables
		cpa[i] = cpb[i];                          // with char pointer variables and square brackets
	}
	
	// *pb = c
	for (i = 0; i < size; i++) {
		// *((char *)pb + i) = c[i];  // original
		// *(cpb + i) = c[i];         // with char pointer variables
		cpb[i] = c[i];                // with char pointer variables and square brackets
	}
	
	// TODO: Think of a way to use only one for loop
}

int main() {
	
	int a = 5;
	int b = 10;

	double c = 3;
	double d = 11;

	swap_any(&a, &b, sizeof(int));
	swap_any(&c, &d, sizeof(double));

	printf("a: %d b: %d\n", a, b);
	printf("c: %f d: %f\n", c, d);
	
	return 0; // return exit code to the calling program
}
