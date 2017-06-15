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
	char c[4096]; // memory to hold the bytes pointed to by 'pa', must be >= 'size', 4096 is big enough for our needs
	
	/*
	 * IDEA: to support any type of variables we must swap all the bytes 
	 * occupied by the two variables
	 */
	
	/*
	 * naively trying to follow the three simple steps used so far leads to problems (see below)
	 * 
	 *   c = *pa;  // store *pa in a temporary variable
	 *   *pa = *pb; // copy *pb in *pa
	 *   *pb = c;  // copy c in *pb
	 */
	
	// c = *pa
	/* the above does not compile for the following reasons:
	 * 
	 *  - the compiler does not know how many bytes to copy to 'c' from 'pa' ('pa' is a void pointer
	 *    and the compiler is not smart enough to know that we keep this information in 'size')
	 * 
	 *  - *more importantly* in C the compiler cannot copy (or compare) arrays
	 *    (i.e. even if 'pa' was of type 'char[4096]' the code 'c = pa' doesn't compile)
	 * 
	 * => we must write code that does the above operation (copying all bytes
	 *    starting from address 'pa' up to 'pa' + 'size' to 'c' up
	 *    to 'c' + 'size')
	 */
	for (i = 0; i < size; i++) {
		// we need the 'i'-th byte starting from address 'pa' so that
		// we can assign it to c[i]
		
		// first let's try to get the byte on address 'pa'
		
		// *pa
		/* the above does not compile (dereferencing a void pointer)
		 * 
		 *  - the compiler does not know how many bytes to read starting from address 'pa'
		 */
		
		// *(char *)pa
		/* the above compiles (casting to char pointer and dereferencing it is ok)
		 *
		 *  - the compiler knows how many bytes to read when the pointer is
		 *  a char pointer - 'sizeof(char)' bytes (1 byte on all platforms)
		 * 
		 *    - a pointer of type T (T* p) always reads 'sizeof(T)' bytes starting
		 *    from address 'p' ('sizeof(T)' can differ from platform to platform)
		 */
		
		// to get the 'i'-th byte starting from address 'pa' we need to 
		// offset the 'pa' pointer by 'i' bytes
		
		// in C we can only offset a pointer by a number of *elements*
		//
		// => we need to cast 'pa' to a pointer whose 'pointed to' element size is 1 byte (a char)
		//    and then offset it
		
		c[i] = *((char *)pa + i); // NOTE: This syntax is not very convenient. TODO: Is there a better way?
	}
	
	// *pa = *pb
	/* the above does not compile:
	 * 
	 *  - 'pa' and 'pb' are void pointers and in C the compiler cannot copy or compare arrays (as in the first step)
	 * 
	 * => we must write code that does the above operation (copying all bytes
	 *    starting from address 'pb' up to 'pb' + 'size' to address 'pa' up
	 *    to 'pa' + 'size')
	 */
	for (i = 0; i < size; i++) {
		// the logic is the same as in step one but this time we must offset both 'pa' and 'pb' with 'i' bytes
		*((char *)pa + i) = *((char *)pb + i); // NOTE: This syntax is not very convenient. TODO: Is there a better way?
	}
	
	// *pb = c
	/* the above does not compile:
	 * 
	 *  - 'pb' is void pointer and in C the compiler cannot copy or compare arrays (as in the previous steps)
	 * 
	 * => we must write code that does the above operation (copying all bytes
	 *    starting from 'c' up to 'c' + 'size' to address 'pb' up
	 *    to 'pb' + 'size')
	 */
	for (i = 0; i < size; i++) {
		// the logic is the same as in step one but this time it is done in reverse
		*((char *)pb + i) = c[i]; // NOTE: This syntax is not very convenient. TODO: Is there a better way?
	}
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
