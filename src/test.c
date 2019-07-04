
#include "test.h"

char const* test1 = "Omae wa mou shindeiru.\0";		size_t const test1_len = 23;
char const* test2 = "Nani???\0";					size_t const test2_len = 8;
char const* test3 = "Un ange mange de la fange.\0";	size_t const test3_len = 27;

char*	nullstr	= "(NULL)";
char*	segstr	= "(segfault)";

void segfault_handler(int sig, siginfo_t *info, void *ptr)
{
    if (sig == SIGSEGV)
    {
        longjmp(restore, SIGSEGV);
    }
}

void	print_nonstd(void)
{
printf("\n");
	printf("\n==> "C_BLUE"The following tests are for the functions which are not present in the standard C library."C_RESET);
	printf("\n==> "C_BLUE"You may decide to protect these functions against segfaults or not, just remain coherent."C_RESET);
}

int		main(int argc, char **argv)
{
	memset(&sig, 0, sizeof(sigaction));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags     = SA_NODEFER;
	sig.sa_sigaction = segfault_handler;
	sigaction(SIGSEGV, &sig, NULL);

	printf("   __   __ ___   _____ ______    ______ _____ ___  ______\n");
	printf("  / /  / // . | / ___//_  __/   /_  __//  __// __|/_  __/\n");
	printf(" / /_ / // , < / __/   / /       / /  /  _/ _\\_ \\  / /   \n");
	printf("/___//_//___-'/_/     /_/       /_/  /____/ \\__-' /_/    \n");
	printf("                                  ==> by duquesne @ 42.fr\n");

	if (argc <= 1)
	{
		int num = 1;
		if (*(char *)&num == 1)
			 printf("\n"C_GREEN"/!\\ Processor is Little-Endian (all tests should work reliably and can be trusted)"C_RESET"\n");
		else printf("\n"C_RED"/!\\ Processor is Big-Endian (errors may arise in certain tests, like 'uint' tests for mem functions)"C_RESET"\n");
		printf("\n"C_YELLOW"All the tests with written in yellow 'can segfault' are NULL pointer tests."C_RESET"\n");

		test_memory();
		test_char();
		test_string();
		test_stringarray();
		test_convert();
		test_color();
		test_list();
		test_math();
		test_vlq();
		test_io();
	}
	else
	{

		for (t_u32 i = 1; i < argc; ++i)
		{
			if (argv[i][0] == '-')
			{
				if (argv[i][1] == '\0') printf("libft_test: Invalid (empty) argument encountered.\n");
				else if (str_equals(argv[i] + 1, "memory"))			test_memory();
				else if (str_equals(argv[i] + 1, "char"))			test_char();
				else if (str_equals(argv[i] + 1, "string"))			test_string();
				else if (str_equals(argv[i] + 1, "stringarray"))	test_stringarray();
				else if (str_equals(argv[i] + 1, "convert"))		test_convert();
				else if (str_equals(argv[i] + 1, "color"))			test_color();
				else if (str_equals(argv[i] + 1, "list"))			test_list();
				else if (str_equals(argv[i] + 1, "math"))			test_math();
				else if (str_equals(argv[i] + 1, "vlq"))			test_vlq();
				else if (str_equals(argv[i] + 1, "io"))				test_io();
				if (argv[i][1] == '\0') printf("libft_test: Argument not recognized: %s.\n", argv[i]);
			}
			else
			{
				printf("libft test: Invalid argument(s), use one of the following:\n");
				printf("\t-memory\n");
				printf("\t-char\n");
				printf("\t-string\n");
				printf("\t-stringarray\n");
				printf("\t-convert\n");
				printf("\t-color\n");
				printf("\t-list\n");
				printf("\t-math\n");
				printf("\t-vlq\n");
				printf("\t-io\n");
			}
		}
	}
	return (OK);
}
