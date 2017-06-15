#include <stdio.h>
#include <stdlib.h>
#define KRED  "\x1B[31m"
#define RESET "\033[0m"

int array_size = 2;
int array[] = {40, 65000};

void printCharAsBools(char c)
{
    int index;
    int comparator = 1;
    for (index = 0; index < 8; index++)
    {
        printf("%d", (c & comparator) ? 1 : 0);
        comparator *= 2;
    }
    printf(" ");
}

void printArray(void *pArray, int array_size, int element_size_in_bytes)
{
    int array_counter, element_counter;
    for (array_counter = 0; array_counter < array_size; array_counter++)
    {
        for (element_counter = 0; element_counter < element_size_in_bytes; element_counter++)
        {
            int offset = array_counter * element_size_in_bytes + element_counter;
            char *byte = pArray + offset;
            printf("%s(%d)%s", KRED, offset, RESET);
            printCharAsBools(*byte);
        }
        printf("\n");
    }
    printf("\n");
}

void swap(void *pValue1, void *pValue2, int element_size_in_bytes)
{
    int index;
    for (index = 0; index < element_size_in_bytes; index++)
    {
        printf("Swapping ");
        printCharAsBools(*(char*)(pValue1));
        printf("With ");
        printCharAsBools(*(char*)(pValue2));
        printf("\n");
        char pTemp = *(char*)(pValue1);
        *(char*)pValue1 = *(char*)pValue2;
        *(char*)pValue2 = pTemp;

        printArray(array, array_size, element_size_in_bytes);

        pValue1++;
        pValue2++;
    }
}

void swapArray(void *pArray, int array_size, int element_size_in_bytes)
{
    int index;
    for (index = 0; index < array_size/2; index++)
    {
        void *pValue1 = pArray + index * element_size_in_bytes;
        void *pValue2 = pArray + (array_size - 1 - index) * element_size_in_bytes;
        swap(pValue1, pValue2, element_size_in_bytes);
    }
}

int main()
{
    //int array_size = 2;
    //int array[] = {40, 65000};
    printf("Array before swap:\n");
    printArray(array, array_size, sizeof(int));
    swapArray(array, array_size, sizeof(int));
    printf("Array after swap:\n");
    printArray(array, array_size, sizeof(int));
    return 1;
}
