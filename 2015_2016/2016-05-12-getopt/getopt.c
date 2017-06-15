#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int aFlag, bFlag, opt;
	aFlag = bFlag = 0;

	while ((opt = getopt(argc, argv, "ab")) != -1)
	{
		switch (opt)
		{
			case 'a':
				aFlag = 1;
				break;
			case 'b':
				bFlag = 1;
				break;
			default:
				printf("Usage %s [-a] [-b]\n", argv[0]);
				return 1;
		}
	} 

	printf("aFlag = %d, bFlag = %d\n", aFlag, bFlag);
	return 0;
}
