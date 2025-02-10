
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <locale.h>

#include "test.h"
#include "test_utils.h"



static char const* program_name = NULL;

/*============================================================================*\
||                           Global Testing Variables                         ||
\*============================================================================*/

char const* test1 = "Omae wa mou shindeiru.";		size_t const test1_len = 23;
char const* test2 = "Nani???";						size_t const test2_len = 8;
char const* test3 = "Un ange mange de la fange.";	size_t const test3_len = 27;

char const* teststr_cc_c0	= "␡␁␂␃␄␅␆␇␈␉␊␋␌␍␎␏␐␑␒␓␔␕␖␗␘␙␚␛␜␝␞␟";
char const* teststr_cc_c1	= "";
char const* teststr_utf8_fr	= "Être à même de ça, d'air sûr — manger du maïs à l'œil… D'où la paix sur l'île de son âme…";
char const* teststr_utf8_ru	= "Яцк Ничолсон ; сталин ленин троцкий хрущев москва";
char const* teststr_utf8_jp	= "お前はもう死んでいる - 愛 - 私は実体の小さな学生です";
char const* teststr_utf8_ho	= "�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻";
char const* teststr_utf8_one_symbol_two_seq =	"\xF0\x9F\x91\x8B"  /* U+1F44B: 'WAVING HAND SIGN' */
												"\xF0\x9F\x8F\xBB"; /* U+1F3FB: 'EMOJI MODIFIER FITZPATRICK TYPE-1-2' */

char const* teststr_utf8_one_symbol_three_seq = "നും"; /* U+0D28, U+0D41, U+0D02 */

char const* teststr_utf8_hardcore	= 
#include "utf8_hardcore.inc"
;

size_t const teststr_utf8_hardcore_len = 5101; // Number of graphemes
size_t const teststr_utf8_hardcore_bytelen = 10037; // Number of bytes, including terminating '\0'






s_program	g_test;



/*============================================================================*\
||                           Main Program Definitions                         ||
\*============================================================================*/

static void	handle_arg_verbose()		{ g_test.config.verbose       = TRUE; }
static void	handle_arg_show_args()		{ g_test.config.show_args     = TRUE; }
static void	handle_arg_show_errors()	{ g_test.config.show_errors   = TRUE; }
static void	handle_arg_show_result()	{ g_test.config.show_result   = TRUE; }
static void	handle_arg_show_escaped()	{ g_test.config.show_escaped  = TRUE; }
static void handle_arg_show_speed()		{ g_test.config.show_speed    = TRUE; }
static void	handle_arg_test_nullptrs()	{ g_test.config.test_nullptrs = TRUE; }
static void	handle_arg_test_overflow()	{ g_test.config.test_overflow = TRUE; }
static void	handle_arg_test_all()
{
	g_test.config.test_nullptrs = TRUE;
	g_test.config.test_overflow = TRUE;
}

/*!
**	This function initializes the global variable 'g_test', which is used everywhere.
*/
static void	init(void)
{
	// default every option to FALSE
	memset(&g_test.config, 0, sizeof(s_test_config));

	static const s_test_suite suites[TEST_SUITE_AMOUNT] =
	{
	#undef ENUM
	#define ENUM(_name_, _func_, _enum_, ...) \
		{ FALSE, _name_, _func_, /*(s_test_totals)*/{ 0 } },
	#include "test_suites.enum"
	#undef ENUM
	};
	memcpy(g_test.suites, suites, sizeof(s_test_suite) * TEST_SUITE_AMOUNT);

	static const s_test_arg args[TEST_ARGS_AMOUNT] =
	{
		{ NULL,						'h', "help",			"If provided, output only the program usage help and exit." },
		{ handle_arg_verbose,		'v', "verbose",			"If provided, output each test result (as either 'OK!' or 'ERROR: return was _')." },
		{ handle_arg_show_args,		'a', "show-args",		"If provided, output the arguments used for each test performed." },
		{ handle_arg_show_errors,	'e', "show-errors",		"If provided, output any errors that occurred during function execution, with the default libccc error handler." },
		{ handle_arg_show_result,	'r', "show-result",		"If provided, output the result for each test performed, even when passed." },
		{ handle_arg_show_escaped,	's', "show-escaped",	"If provided, output any non-printable characters as a backslash C escape sequence." },
		{ handle_arg_show_speed,	'p', "show-performance","If provided, output the execution speed for each test performed." },
		{ handle_arg_test_all,		't', "test-all",		"Sets all the 'test-something' arguments below (is equivalent to doing '-no')" },
		{ handle_arg_test_nullptrs,	'n', "test-nullptrs",	"If provided, perform the NULL pointer tests for all functions." },
		{ handle_arg_test_overflow,	'o', "test-overflow",	"If provided, perform the overflowing number tests for 'libccc_convert' functions." },
	};
	memcpy(g_test.args, args, sizeof(s_test_arg) * TEST_ARGS_AMOUNT);
}



/*============================================================================*\
||                             Main Program Logic                             ||
\*============================================================================*/

// A special return value to signal when a help argument has been provided by the user
#define MATCHED_HELP	((int)-1)



static
int	handle_args_test_suites(char const* arg)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.suites[i].name))
		{
			g_test.suites[i].run = TRUE;
			return (TRUE);
		}
	}
	return (FALSE);
}

static
int	handle_args_option_char(char arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (arg == g_test.args[i].arg)
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}

static
int	handle_args_option_string(char const* arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.args[i].name))
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}



int	main(int argc, char** argv)
{
	if (argc < 1 || argv == NULL || argv[0] == NULL)
	{
		print_error("Invalid platform, no 'argv' program argument list received.");
		return (ERROR);
	}
	program_name = argv[0];

	init();
	init_signal_handler();
	// set locale to null
	setlocale(LC_ALL, "");

	// Handle main program arguments
	int	match;
	int tmp;
	for (int i = 1; i < argc; ++i)
	{
		match = FALSE;
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '\0')
			{
				print_error("Unexpected end of argument after '-'.");
				continue;
			}
			else if (argv[i][1] == '-')
			{
				match = handle_args_option_string(argv[i] + 2);
			}
			else for (size_t j = 1; j < strlen(argv[i]); ++j)
			{
				tmp = handle_args_option_char(argv[i][j]);
				if (match)
					match = (tmp == MATCHED_HELP ? tmp : match);
				else match = tmp;
			}
		}
		else if (isalpha(argv[i][0]))
		{
			match = handle_args_test_suites(argv[i]);
		}

		if (match == FALSE)
		{
			print_error("Argument not recognized (%s)\n", argv[i]);
			print_usage(program_name);
			return (ERROR);
		}
		else if (match == MATCHED_HELP)
		{
			print_usage(program_name);
			return (OK);
		}
	}

	// Run the appropriate test suites
	print_title();
	print_endian_warning();
	test_init();
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (g_test.suites[i].run)
		{
			g_test.current_suite = (e_test_suite_libccc)i;
			g_test.suites[i].test();
			if (g_test.suites[i].totals.tests)
			{
				print_totals(
					g_test.suites[i].totals.tests,
					g_test.suites[i].totals.failed,
					g_test.suites[i].totals.warnings,
					g_test.suites[i].name);
			}
		}
	}
	if (print_results(g_test.suites))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
