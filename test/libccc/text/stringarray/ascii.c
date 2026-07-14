
#include "libccc/stringarray.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



char const*		strarr_empty[1] = {NULL};

char const*		strarr1_as_str =
"Les sanglots longs\
\nDes violons\
\n\tDe l'automne\
\nBlessent mon cœur\
\nD'une langueur\
\n\tMonotone.\
\nTout suffocant\
\nEt blême, quand\
\n\tSonne l'heure,\
\nJe me souviens\
\nDes jours anciens\
\n\tEt je pleure;\
\nEt je m'en vais\
\nAu vent mauvais\
\n\tQui m'emporte\
\nDeçà, delà,\
\nPareil à la\
\n\tFeuille morte.";

char const*		strarr1_A[19] =
{
	"Les sanglots longs",
	"Des violons",
	"\tDe l'automne",
	"Blessent mon cœur",
	"D'une langueur",
	"\tMonotone.",
	"Tout suffocant",
	"Et blême, quand",
	"\tSonne l'heure,",
	"Je me souviens",
	"Des jours anciens",
	"\tEt je pleure;",
	"Et je m'en vais",
	"Au vent mauvais",
	"\tQui m'emporte",
	"Deçà, delà,",
	"Pareil à la",
	"\tFeuille morte.",
	NULL
};

char const*		strarr1_B[19] =
{
	"Les sanglots longs",
	"Des violons",
	"De l'automne",
	"Blessent mon cœur",
	"D'une langueur",
	"Monotone.",
	"Tout suffocant",
	"Et blême, quand",
	"Sonne l'heure,",
	"Je me souviens",
	"Des jours anciens",
	"Et je pleure;",
	"Et je m'en vais",
	"Au vent mauvais",
	"Qui m'emporte",
	"Deçà, delà,",
	"Pareil à la",
	"Feuille morte.",
	NULL
};

char const*		strarr1_C[8] =
{
	"Les sanglots longs\nDes violons",
	"De l'automne\nBlessent mon cœur\nD'une langueur",
	"Monotone.\nTout suffocant\nEt blême, quand",
	"Sonne l'heure,\nJe me souviens\nDes jours anciens",
	"Et je pleure;\nEt je m'en vais\nAu vent mauvais",
	"Qui m'emporte\nDeçà, delà,\nPareil à la",
	"Feuille morte.",
	NULL
};

char const*		strarr2_as_str = "Un ange mange de la fange.\n";
char const*		strarr2_A[5] = { "Un ", " m", " de la f", ".\n", NULL };
char const*		strarr2_B[6] = { "Un ", "nge m", "nge de l", " f", "nge.\n", NULL };

char const*		strarr3_as_str_A = "Omae wa mou shindeiru.";
char const*		strarr3_as_str_B = "  Omae wa mou \t shindeiru.\n";
char const*		strarr3[5] = { "Omae", "wa", "mou", "shindeiru.", NULL};

char const*		strarr4_as_str = "aabbaaabbaa";
char const*		strarr4_A[3] = {"bb", "bb", NULL};
char const*		strarr4_B[5] = {"", "bb", "abb", "", NULL};
char const*		strarr4_C[9] = {"", "", "bb", "", "", "bb", "", "", NULL};


/*============================================================================*\
||                        Basic StringArray Operations                        ||
\*============================================================================*/



#ifndef c_strarrlen
void test_strarrlen(void)	{}
#warning "strarrlen() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrlen(char const* test_name, t_testflags flags,
		t_size			expecting,
		char const**	strarr)
{
	char* tmp = NULL;
	TEST_INIT(size)
	TEST_PERFORM(	strarrlen, strarr)
	TEST_PRINT(size,strarrlen, "strarr=[ %s ]", tmp) // TODO
}
void	test_strarrlen()
{
//	| TEST FUNCTION		| TEST NAME				| TESTFLAG	| EXPECTING | TEST ARGS
	print_test_strarrlen("strarrlen",				FALSE,		18,         strarr1_A);
	print_test_strarrlen("strarrlen",				FALSE,		18,         strarr1_B);
	print_test_strarrlen("strarrlen",				FALSE,		 7,         strarr1_C);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr2_A);
	print_test_strarrlen("strarrlen",				FALSE,		 5,         strarr2_B);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr3);
	print_test_strarrlen("strarrlen",				FALSE,		 2,         strarr4_A);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr4_B);
	print_test_strarrlen("strarrlen",				FALSE,		 8,         strarr4_C);
	print_test_strarrlen("strarrlen (null strarr)",	TRUE,		 0,         NULL);
}
#endif



#ifndef c_strsplit_char
void test_strsplit_char(void)	{}
#warning "strsplit_char() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_char(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char			separator)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_char, str, separator)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_char, "str=\"%s\", sep='%c'/0x%2X", str, separator, separator)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_char()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG		| EXPECTING				| TEST ARGS
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr1_A,				strarr1_as_str,		'\n');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr2_B,				strarr2_as_str,		'a');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr3,				strarr3_as_str_A,	' ');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr4_A,				strarr4_as_str,		'a');
	print_test_strsplit_char("strsplit_char (null str)",ALLOW_SIGSEGV,	NULL,					NULL,				'a');
}
#endif



#ifndef c_strsplit_cset
void test_strsplit_cset(void)	{}
#warning "strsplit_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_cset(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char const*		separators)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_cset, str, separators)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_cset, "str=\"%s\", seps=\"%s\"", str, separators)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_cset()
{
	char const* numbers[4] = {"2130706433", "136661", "46", NULL};
//	| TEST FUNCTION				| TEST NAME						| TESTFLAG		| EXPECTING			| TEST ARGS
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr1_A,			strarr1_as_str,				"\n");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr1_B,			strarr1_as_str,				"\n\t");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr2_B,			strarr2_as_str,				"a");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr3,			strarr3_as_str_A,			" ");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr3,			strarr3_as_str_B,			" \n\t");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr4_A,			strarr4_as_str,				"a");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr_empty,		strarr4_as_str,				"ab");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			numbers,			"2130706433 136661 46",		" ");
	print_test_strsplit_cset("strsplit_cset (null str)",	ALLOW_SIGSEGV,	NULL,				NULL,						"a");
	print_test_strsplit_cset("strsplit_cset (null seps)",	ALLOW_SIGSEGV,	NULL,				strarr1_as_str,				NULL);
	print_test_strsplit_cset("strsplit_cset (both null)",	ALLOW_SIGSEGV,	NULL,				NULL,						NULL);
}
#endif



#ifndef c_strsplit_str
void test_strsplit_str(void)	{}
#warning "strsplit_str() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_str(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char const*		separator)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_str, str, separator)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_str, "str=\"%s\", sep=\"%s\"", str, separator)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_str()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING				| TEST ARGS
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr1_A,			strarr1_as_str,		"\n");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr1_C,			strarr1_as_str,		"\n\t");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr2_A,			strarr2_as_str,		"ange");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr2_B,			strarr2_as_str,		"a");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr3,			strarr3_as_str_A,	" ");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr4_B,			strarr4_as_str,		"aa");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr4_C,			strarr4_as_str,		"a");
	print_test_strsplit_str("strsplit_str (null str)",	ALLOW_SIGSEGV,	NULL,				NULL,				"a");
	print_test_strsplit_str("strsplit_str (null seps)",	ALLOW_SIGSEGV,	NULL,				strarr1_as_str,		NULL);
	print_test_strsplit_str("strsplit_str (both null)",	ALLOW_SIGSEGV,	NULL,				NULL,				NULL);
}
#endif



#ifndef c_strjoin
void test_strjoin(void)	{}
#warning "strjoin() test suite function defined, but the function isn't defined."
#else
void	print_test_strjoin(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const**	strarr,
		char const*		sep)
{
	TEST_INIT(str)
	TEST_PERFORM(	strjoin, strarr, sep)
//	TEST_PRINT(str,	strjoin, "strarr=[ %s ], sep=\"%s\", strarr, sep) // TODO
	TEST_FREE()
}
void	test_strjoin()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING			| TEST ARGS
	print_test_strjoin("strjoin",					FALSE,			strarr1_as_str,		strarr1_A,	"\n");
	print_test_strjoin("strjoin",					FALSE,			strarr1_as_str,		strarr1_C,	"\n\t");
	print_test_strjoin("strjoin",					FALSE,			strarr2_as_str,		strarr2_A,	"ange");
	print_test_strjoin("strjoin",					FALSE,			strarr2_as_str,		strarr2_B,	"a");
	print_test_strjoin("strjoin",					FALSE,			strarr3_as_str_A,	strarr3,	" ");
	print_test_strjoin("strjoin",					FALSE,			strarr4_as_str,		strarr4_B,	"aa");
	print_test_strjoin("strjoin (null strarr)",		ALLOW_SIGSEGV,	NULL,				NULL,		"");
	print_test_strjoin("strjoin (null sep)   ",		ALLOW_SIGSEGV,	NULL,				strarr3,	NULL);
	print_test_strjoin("strjoin (both null)  ",		ALLOW_SIGSEGV,	NULL,				NULL,		NULL);
}
#endif



#ifndef c_strarrconcat
void test_strarrconcat(void)	{}
#warning "strarrconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrconcat(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr1,
		char const**	strarr2)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrconcat, strarr1, strarr2)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrconcat, "strarr1=[ %p ], strarr2=[ %p ]", (void*)strarr1, (void*)strarr2) // TODO
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrconcat()
{
	static char const*	expect[7] = { "Un ", " m", " de la f", ".\n", "bb", "bb", NULL };
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING			| TEST ARGS
	print_test_strarrconcat("strarrconcat",				FALSE,		expect,			strarr2_A,		strarr4_A);
	print_test_strarrconcat("strarrconcat (lhs empty)",	FALSE,		strarr4_A,		strarr_empty,	strarr4_A);
	print_test_strarrconcat("strarrconcat (rhs empty)",	FALSE,		strarr3,		strarr3,		strarr_empty);
}
#endif





/*============================================================================*\
||                       Additional StringArray Operations                    ||
\*============================================================================*/



#ifndef c_strarrlens
void test_strarrlens(void)	{}
#warning "strarrlens() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrlens(char const* test_name, t_testflags flags,
		t_size			expecting,
		char const**	strarr,
		t_uint			n)
{
	TEST_INIT(size)
	TEST_PERFORM(	strarrlens, strarr, n)
	TEST_PRINT(size,strarrlens, "strarr=%p, n=" SF_UINT, (void*)strarr, n)
}
void	test_strarrlens(void)
{
//	| TEST FUNCTION       | TEST NAME                    | TESTFLAGS      | EXPECTING | TEST ARGS
	print_test_strarrlens("strarrlens              ",      FALSE          , 19,         strarr3, 4);
	print_test_strarrlens("strarrlens (capped)     ",      FALSE          ,  6,         strarr3, 2);
	print_test_strarrlens("strarrlens (n too big)  ",      FALSE          , 19,         strarr3, 99);
	print_test_strarrlens("strarrlens (null strarr)",      ALLOW_SIGSEGV  ,  0,         NULL, 4);
}
#endif



#ifndef c_strdivide
void test_strdivide(void)	{}
#warning "strdivide() test suite function defined, but the function isn't defined."
#else
void	print_test_strdivide(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		t_size			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strdivide, str, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strdivide, "str=\"%s\", n=" SF_SIZE, str, n)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strdivide(void)
{
	static char const*	expect_4[4] = { "aabb", "aaab", "baa", NULL };
	static char const*	expect_whole[2] = { "aabbaaabbaa", NULL };
//	| TEST FUNCTION      | TEST NAME                   | TESTFLAGS      | EXPECTING     | TEST ARGS
	print_test_strdivide("strdivide               ",     FALSE          , expect_4,       strarr4_as_str, 4);
	print_test_strdivide("strdivide (n > length)  ",     FALSE          , expect_whole,   strarr4_as_str, 99);
	print_test_strdivide("strdivide (null str)    ",     ALLOW_SIGSEGV  , NULL,           NULL, 4);
}
#endif



#ifndef c_strarrequ
void test_strarrequ(void)	{}
#warning "strarrequ() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrequ(char const* test_name, t_testflags flags,
		t_bool			expecting,
		char const**	strarr1,
		char const**	strarr2)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strarrequ, strarr1, strarr2)
	TEST_PRINT(bool,strarrequ, "strarr1=%p, strarr2=%p", (void*)strarr1, (void*)strarr2)
}
void	test_strarrequ(void)
{
	static char const*	same_as_strarr4_A[3] = { "bb", "bb", NULL };
	static char const*	different[3] = { "bb", "XX", NULL };
//	| TEST FUNCTION      | TEST NAME                          | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrequ("strarrequ (equal content)      ",     FALSE     , TRUE ,      strarr4_A, same_as_strarr4_A);
	print_test_strarrequ("strarrequ (same pointer)       ",     FALSE     , TRUE ,      strarr4_A, strarr4_A);
	print_test_strarrequ("strarrequ (different content)  ",     FALSE     , FALSE,      strarr4_A, different);
	print_test_strarrequ("strarrequ (different lengths)  ",     FALSE     , FALSE,      strarr4_A, strarr3);
	print_test_strarrequ("strarrequ (empty vs empty)     ",     FALSE     , TRUE ,      strarr_empty, strarr_empty);
}
#endif



#ifndef c_strarrfindi
void test_strarrfindi(void)	{}
#warning "strarrfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrfindi(char const* test_name, t_testflags flags,
		t_sint			expecting,
		char const**	strarr,
		char const*		str)
{
	TEST_INIT(sint)
	TEST_PERFORM(	strarrfindi, strarr, str)
	TEST_PRINT(sint,strarrfindi, "strarr=%p, str=\"%s\"", (void*)strarr, str)
}
void	test_strarrfindi(void)
{
//	| TEST FUNCTION        | TEST NAME                  | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrfindi("strarrfindi            ",     FALSE     , 2,          strarr3, "mou");
	print_test_strarrfindi("strarrfindi (first)    ",     FALSE     , 0,          strarr4_A, "bb");
	print_test_strarrfindi("strarrfindi (empty)    ",     FALSE     , 0,          strarr4_B, "");
	print_test_strarrfindi("strarrfindi (absent)   ",     FALSE     , ERROR,      strarr3, "zz");
}
#endif



#ifndef c_strarrcount_char
void test_strarrcount_char(void)	{}
#warning "strarrcount_char() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrcount_char(char const* test_name, t_testflags flags,
		t_uint			expecting,
		char const**	strarr,
		char			c)
{
	TEST_INIT(uint)
	TEST_PERFORM(	strarrcount_char, strarr, c)
	TEST_PRINT(uint,strarrcount_char, "strarr=%p, c='%c'", (void*)strarr, c)
}
void	test_strarrcount_char(void)
{
//	| TEST FUNCTION             | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrcount_char("strarrcount_char          ",     FALSE     , 2,          strarr3, 'a');
	print_test_strarrcount_char("strarrcount_char          ",     FALSE     , 4,          strarr4_A, 'b');
	print_test_strarrcount_char("strarrcount_char (absent) ",     FALSE     , 0,          strarr4_A, 'z');
}
#endif



#ifndef c_strarrcount_cset
void test_strarrcount_cset(void)	{}
#warning "strarrcount_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrcount_cset(char const* test_name, t_testflags flags,
		t_uint			expecting,
		char const**	strarr,
		char const*		cset)
{
	TEST_INIT(uint)
	TEST_PERFORM(	strarrcount_cset, strarr, cset)
	TEST_PRINT(uint,strarrcount_cset, "strarr=%p, cset=\"%s\"", (void*)strarr, cset)
}
void	test_strarrcount_cset(void)
{
//	| TEST FUNCTION             | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrcount_cset("strarrcount_cset         ",     FALSE     , 9,          strarr3, "aeiou");
	print_test_strarrcount_cset("strarrcount_cset (absent)",     FALSE     , 0,          strarr4_A, "xyz");
}
#endif



#ifndef c_strarrcount_str
void test_strarrcount_str(void)	{}
#warning "strarrcount_str() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrcount_str(char const* test_name, t_testflags flags,
		t_uint			expecting,
		char const**	strarr,
		char const*		query)
{
	TEST_INIT(uint)
	TEST_PERFORM(	strarrcount_str, strarr, query)
	TEST_PRINT(uint,strarrcount_str, "strarr=%p, query=\"%s\"", (void*)strarr, query)
}
void	test_strarrcount_str(void)
{
//	| TEST FUNCTION            | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrcount_str("strarrcount_str          ",     FALSE     , 4,          strarr4_A, "b");
	print_test_strarrcount_str("strarrcount_str          ",     FALSE     , 1,          strarr3, "shin");
	print_test_strarrcount_str("strarrcount_str (absent) ",     FALSE     , 0,          strarr3, "zz");
}
#endif



#ifndef c_strarrsub
void test_strarrsub(void)	{}
#warning "strarrsub() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrsub(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr,
		t_uint			index,
		t_uint			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrsub, strarr, index, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrsub, "strarr=%p, index=" SF_UINT ", n=" SF_UINT, (void*)strarr, index, n)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrsub(void)
{
	static char const*	expect[3] = { "wa", "mou", NULL };
	// NOTE: out-of-bounds cases (which return NULL) are covered elsewhere,
	// because print_test_strarr() does not support a NULL result/expect without ALLOW_SIGSEGV.
//	| TEST FUNCTION      | TEST NAME             | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrsub("strarrsub         ",     FALSE     , expect,     strarr3, 1, 2);
	print_test_strarrsub("strarrsub (whole) ",     FALSE     , strarr3,    strarr3, 0, 4);
}
#endif



#ifndef c_strarrrev
void test_strarrrev(void)	{}
#warning "strarrrev() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrrev(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrrev, strarr)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrrev, "strarr=%p", (void*)strarr)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrrev(void)
{
	static char const*	expect[5] = { "shindeiru.", "mou", "wa", "Omae", NULL };
//	| TEST FUNCTION      | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrrev("strarrrev           ",     FALSE     , expect,     strarr3);
	print_test_strarrrev("strarrrev (palindrome)",   FALSE     , strarr4_A,  strarr4_A);
}
#endif



#ifndef c_strarrpadl
void test_strarrpadl(void)	{}
#warning "strarrpadl() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrpadl(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr,
		char			c,
		t_uint			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrpadl, strarr, c, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrpadl, "strarr=%p, c='%c', n=" SF_UINT, (void*)strarr, c, n)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrpadl(void)
{
	static char const*	expect[3] = { "--bb", "--bb", NULL };
//	| TEST FUNCTION       | TEST NAME       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrpadl("strarrpadl   ",     FALSE     , expect,     strarr4_A, '-', 4);
}
#endif



#ifndef c_strarradd
void test_strarradd(void)	{}
#warning "strarradd() test suite function defined, but the function isn't defined."
#else
void	print_test_strarradd(char const* test_name, t_testflags flags,
		char const**	expecting,
		char**			dest,
		char const*		str)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarradd, dest, str)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarradd, "str=\"%s\"", str)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarradd(void)
{
	static char const*	expect[4] = { "bb", "bb", "cc", NULL };
	static char const*	expect_1[2] = { "cc", NULL };
	// NOTE: `dest` must be heap-allocated, since StringArray_Add() reallocates it (and the result owns it).
//	| TEST FUNCTION      | TEST NAME             | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarradd("strarradd          ",     FALSE     , expect,     c_strarrdup(strarr4_A), "cc");
	print_test_strarradd("strarradd (empty)  ",     FALSE     , expect_1,   c_strarrdup(strarr_empty), "cc");
}
#endif



#ifndef c_strarrrep
void test_strarrrep(void)	{}
#warning "strarrrep() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrrep(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr,
		char const*		str_old,
		char const*		str_new)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrrep, strarr, str_old, str_new)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrrep, "strarr=%p, old=\"%s\", new=\"%s\"", (void*)strarr, str_old, str_new)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrrep(void)
{
	static char const*	expect[3] = { "XX", "XX", NULL };
//	| TEST FUNCTION      | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrrep("strarrrep           ",     FALSE     , expect,     strarr4_A, "bb", "XX");
	print_test_strarrrep("strarrrep (absent)  ",     FALSE     , strarr3,    strarr3, "zz", "yy");
}
#endif



#ifndef c_strarrrepfirst
void test_strarrrepfirst(void)	{}
#warning "strarrrepfirst() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrrepfirst(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr,
		char const*		str_old,
		char const*		str_new,
		t_uint			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrrepfirst, strarr, str_old, str_new, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrrepfirst, "strarr=%p, old=\"%s\", new=\"%s\", n=" SF_UINT, (void*)strarr, str_old, str_new, n)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrrepfirst(void)
{
	static char const*	expect[3] = { "XX", "bb", NULL };
//	| TEST FUNCTION           | TEST NAME           | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrrepfirst("strarrrepfirst  ",      FALSE     , expect,     strarr4_A, "bb", "XX", 1);
}
#endif



#ifndef c_strarrreplast
void test_strarrreplast(void)	{}
#warning "strarrreplast() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrreplast(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr,
		char const*		str_old,
		char const*		str_new,
		t_uint			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrreplast, strarr, str_old, str_new, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrreplast, "strarr=%p, old=\"%s\", new=\"%s\", n=" SF_UINT, (void*)strarr, str_old, str_new, n)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrreplast(void)
{
	static char const*	expect[3] = { "bb", "XX", NULL };
//	| TEST FUNCTION          | TEST NAME           | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_strarrreplast("strarrreplast  ",       FALSE     , expect,     strarr4_A, "bb", "XX", 1);
}
#endif


/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_stringarray_ascii(void)
{
	print_suite_title("libccc/text/stringarray/ascii");

	print_nonstd();



	test_strarrlen();
	test_strarrlens();

//	test_strarrnew();
//	test_strarrcnew();
//	test_strarrdel();

	test_strsplit_char();
	test_strsplit_cset();
	test_strsplit_str();
	test_strdivide();
	test_strjoin();

	test_strarrequ();
	test_strarrfindi();

	test_strarrcount_char();
	test_strarrcount_cset();
	test_strarrcount_str();

	test_strarrpadl();

	test_strarradd();
	test_strarrconcat();
	test_strarrsub();
	test_strarrrev();
	test_strarrrep();
	test_strarrrepfirst();
	test_strarrreplast();

//	test_strarriter();
//	test_strarriiter();
//	test_strarrmap();
//	test_strarrimap();
//	test_strarrfilter();
//	test_strarrifilter();
//	test_strarrreduce();
//	test_strarrireduce();
//	test_strarrfold();
//	test_strarrifold();

	return (0);
}
