
#include <stdlib.h>
#include <stdio.h>



#define OK		(0)
#define ERROR	(1)

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Takes a number 'n' as argument; allocates a memory region that is 'n' bytes long.\n"
			"Prints the preceding area of memory (as a 'size_t'), to check if your C stdlib implementation"
			" has the region's 'size_t' size stored before immediately the pointer returned by malloc().\n"
			"If this program segfaults, or outputs a number which is not the same as the given argument 'n',"
			" then that means that your machine's implementation is different.\n");
		return (ERROR);
	}
	size_t	arg = atoi(argv[1]);
	size_t* region = malloc(arg);
	region -= 1;
	printf("%zu\n", *region);
	++region;
	free(region);
	return (OK);
}
