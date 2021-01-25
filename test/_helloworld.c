
#include <stdio.h>



#define OK		(0)
#define ERROR	(1)

int main(int argc, char** argv)
{
	printf("Hello world!\nprogram args:\n");
	for (int i = 0; i < argc; ++i)
	{
		printf("\t%s\n", argv[i]);
	}
	return (OK);
}
