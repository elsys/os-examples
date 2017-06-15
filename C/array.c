#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int size;
	int* start;
	
} array;

array createArray(int size) {
	if(size < 10) {
		size = 10;
	}
	
	array arr;
	arr.size = size;
	arr.start = malloc(sizeof(int) * size);
	
	return arr;
}

void destroyArray(array *arr) {
	free(arr->start);
}

void addElement(array *arr, int index, int element) {
	if(index >= arr->size) {
		int *tmp = arr->start;
		int i;
		int newsize = arr->size*2;
		
		printf("Resizing array from %d to %d\n", arr->size, newsize);
		
		arr->start = malloc(sizeof(int) * newsize);
		for(i = 0; i < arr->size; i++) {
			arr->start[i] = tmp[i];
		}
		arr->size = newsize;
		free(tmp);
	}
	
	arr->start[index] = element;
}

int getElement(array *arr, int index) {
	return arr->start[index];
}


int main() {
	int i;
	array arr = createArray(10);
	
	for(i = 0; i < 1000; i++) {
		addElement(&arr, i, i * 10);
	}
	
	for(i = 0; i < 1000; i++) {
		printf("arr[%d] = %d\n", i, getElement(&arr, i));
	}
	
	destroyArray(&arr);
}
