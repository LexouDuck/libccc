
#include "libccc/generic/array.c"
#include "libccc/generic/list.c"
#include "libccc/generic/set.c"
#include "libccc/generic/dict.c"
#include "libccc/generic/convert.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	conversion functions (ie: `T` is `void*`, and `T_NAME` is `any`).
**	The array/list/set/dict generic types are all instantiated above, since
**	the conversion functions require them (and in particular, they must be
**	included *before* the "convert.c" generic import file).
**
**	With this instantiation, the `T_EQUALS()` macro is a simple pointer
**	comparison: so, the `*_ToSet` conversions deduplicate by pointer identity.
**	The values used are `char*` strings, so that expected results can be
**	written legibly, with dedicated serializers for each compound type:
**	arrays as `"[a, b]"`, lists as `"[a, b]"`, sets as `"{a, b}"`,
**	key/value pair buffers as `"[key1:value1][key2:value2]"`.
*/

//! The values used to build the test containers
static char* const	g_cvt_val[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};

//! Serializes the given array of `char*` values into a newly allocated string: `"[a, b]"`
static
char*	gen_cvt_array_tostr(s_array(any) const* array)
{
	size_t	length = 2;
	char*	result;
	t_uint	i;

	if (array == NULL)
		return (strdup("(null)"));
	for (i = 0; i < array->length; ++i)
		length += strlen((char const*)array->items[i]) + 2;
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strcpy(result, "[");
	for (i = 0; i < array->length; ++i)
	{
		if (i > 0)
			strcat(result, ", ");
		strcat(result, (char const*)array->items[i]);
	}
	strcat(result, "]");
	return (result);
}

//! Serializes the given list of `char*` values into a newly allocated string: `"[a, b]"`
//! NOTE: a `NULL` list serializes as `"[]"` (an empty list is a `NULL` pointer)
static
char*	gen_cvt_list_tostr(s_list(any) const* list)
{
	size_t	length = 2;
	char*	result;
	s_list(any) const*	elem;

	for (elem = list; elem != NULL; elem = elem->next)
		length += strlen((char const*)elem->item) + 2;
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strcpy(result, "[");
	for (elem = list; elem != NULL; elem = elem->next)
	{
		if (elem != list)
			strcat(result, ", ");
		strcat(result, (char const*)elem->item);
	}
	strcat(result, "]");
	return (result);
}

//! Serializes the given set of `char*` values into a newly allocated string: `"{a, b}"`
static
char*	gen_cvt_set_tostr(s_set(any) const* set)
{
	size_t	length = 2;
	char*	result;
	t_uint	i;

	if (set == NULL)
		return (strdup("(null)"));
	for (i = 0; i < set->length; ++i)
		length += strlen((char const*)set->items[i]) + 2;
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strcpy(result, "{");
	for (i = 0; i < set->length; ++i)
	{
		if (i > 0)
			strcat(result, ", ");
		strcat(result, (char const*)set->items[i]);
	}
	strcat(result, "}");
	return (result);
}

//! Creates the canonical (JoJo) test array with `n` items (in order, no duplicates)
static
s_array(any)*	gen_cvt_array_fixture(t_uint n)
{
	s_array(any)*	result = c_arrnew(any)(n, NULL);
	if (result == NULL)
		return (NULL);
	for (t_uint i = 0; i < n && i < 4; ++i)
		result->items[i] = g_cvt_val[i];
	return (result);
}

//! Creates the canonical (JoJo) test list with `n` items (in order, no duplicates)
static
s_list(any)*	gen_cvt_list_fixture(t_uint n)
{
	s_list(any)*	result = NULL;
	while (n--)
	{
		s_list(any)*	node = c_lstitem(any)(g_cvt_val[n < 4 ? n : 3]);
		if (node == NULL)
			return (NULL);
		node->next = result;
		result = node;
	}
	return (result);
}



/*============================================================================*\
||                          Array <-> List Conversions                        ||
\*============================================================================*/

#ifndef c_arrtolst
void test_arrtolst(void)	{}
#warning "arrtolst() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrtolst(t_uint variant)
{
	s_array(any)*	array;
	s_list(any)*	list;
	char*	result;

	if (variant == 0) // convert a filled array
		array = gen_cvt_array_fixture(4);
	else if (variant == 1) // convert an empty array: gives an empty (`NULL`) list
		array = gen_cvt_array_fixture(0);
	else if (variant == 2) // NULL array: error
	{
		list = c_arrtolst(any)(NULL);
		return (strdup(list == NULL ? "(null)" : "(non-null)"));
	}
	else return (strdup("(bad variant)"));
	list = c_arrtolst(any)(array);
	result = gen_cvt_list_tostr(list);
	if (list != NULL)
		c_lstdel(any)(&list);
	c_arrdel(any)(&array);
	return (result);
}
void	print_test_arrtolst(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrtolst, variant)
	TEST_PRINT(str,	arrtolst, "variant=%u", variant)
	TEST_FREE()
}
void	test_arrtolst(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                            | ARGS
	print_test_arrtolst("arrtolst (filled)      ",	FALSE,	"[Omae,  wa , mou , shindeiru.]",      0);
	print_test_arrtolst("arrtolst (empty array) ",	FALSE,	"[]",                                  1);
	print_test_arrtolst("arrtolst (null array)  ",	FALSE,	"(null)",                              2);
}
#endif



#ifndef c_lsttoarr
void test_lsttoarr(void)	{}
#warning "lsttoarr() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lsttoarr(t_uint variant)
{
	s_list(any)*	list;
	s_array(any)*	array;
	char*	result;

	if (variant == 0) // convert a filled list
	{
		list = gen_cvt_list_fixture(4);
		array = c_lsttoarr(any)(list);
		result = gen_cvt_array_tostr(array);
		if (array != NULL)
			c_arrdel(any)(&array);
		c_lstdel(any)(&list);
		return (result);
	}
	else if (variant == 1) // NULL list: error (NOTE: an empty list *is* `NULL`, so it cannot be converted)
	{
		array = c_lsttoarr(any)(NULL);
		return (gen_cvt_array_tostr(array));
	}
	else if (variant == 2) // round-trip: array -> list -> array must be equal to the original
	{
		s_array(any)*	source = gen_cvt_array_fixture(3);
		list = c_arrtolst(any)(source);
		array = c_lsttoarr(any)(list);
		result = strdup(c_arrequ(any)(source, array) ? "(round-trip equals)" : "(round-trip differs)");
		c_arrdel(any)(&array);
		c_lstdel(any)(&list);
		c_arrdel(any)(&source);
		return (result);
	}
	return (strdup("(bad variant)"));
}
void	print_test_lsttoarr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lsttoarr, variant)
	TEST_PRINT(str,	lsttoarr, "variant=%u", variant)
	TEST_FREE()
}
void	test_lsttoarr(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                            | ARGS
	print_test_lsttoarr("lsttoarr (filled)      ",	FALSE,	"[Omae,  wa , mou , shindeiru.]",      0);
	print_test_lsttoarr("lsttoarr (null list)   ",	FALSE,	"(null)",                              1);
	print_test_lsttoarr("lsttoarr (round-trip)  ",	FALSE,	"(round-trip equals)",                 2);
}
#endif



/*============================================================================*\
||                       Array/List <-> Set Conversions                       ||
\*============================================================================*/

#ifndef c_arrtoset
void test_arrtoset(void)	{}
#warning "arrtoset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrtoset(t_uint variant)
{
	s_array(any)*	array;
	s_set(any)*	set;
	char*	result;

	if (variant == 0) // convert an array without duplicates
		array = gen_cvt_array_fixture(3);
	else if (variant == 1) // convert an array with duplicates: they are removed
	{
		array = c_arrnew(any)(6, NULL);
		array->items[0] = g_cvt_val[0];
		array->items[1] = g_cvt_val[1];
		array->items[2] = g_cvt_val[0]; // duplicate
		array->items[3] = g_cvt_val[2];
		array->items[4] = g_cvt_val[1]; // duplicate
		array->items[5] = g_cvt_val[0]; // duplicate
	}
	else if (variant == 2) // convert an empty array: gives an empty set
		array = gen_cvt_array_fixture(0);
	else if (variant == 3) // NULL array: error
	{
		set = c_arrtoset(any)(NULL);
		return (gen_cvt_set_tostr(set));
	}
	else return (strdup("(bad variant)"));
	set = c_arrtoset(any)(array);
	result = gen_cvt_set_tostr(set);
	if (set != NULL)
		c_setdel(any)(&set);
	c_arrdel(any)(&array);
	return (result);
}
void	print_test_arrtoset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrtoset, variant)
	TEST_PRINT(str,	arrtoset, "variant=%u", variant)
	TEST_FREE()
}
void	test_arrtoset(void)
{
//	| TEST FUNCTION    | TEST NAME                  |TESTFLAG| EXPECTING                | ARGS
	print_test_arrtoset("arrtoset (no duplicates) ",	FALSE,	"{Omae,  wa , mou }",      0);
	print_test_arrtoset("arrtoset (deduplicates)  ",	FALSE,	"{Omae,  wa , mou }",      1);
	print_test_arrtoset("arrtoset (empty array)   ",	FALSE,	"{}",                      2);
	print_test_arrtoset("arrtoset (null array)    ",	FALSE,	"(null)",                  3);
}
#endif



#ifndef c_settoarr
void test_settoarr(void)	{}
#warning "settoarr() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_settoarr(t_uint variant)
{
	s_set(any)*	set;
	s_array(any)*	array;
	char*	result;

	if (variant == 0) // convert a filled set
		set = c_setcreate(any)(3, g_cvt_val[0], g_cvt_val[1], g_cvt_val[2]);
	else if (variant == 1) // convert an empty set: gives an empty array
		set = c_setnew(any)();
	else if (variant == 2) // NULL set: error
	{
		array = c_settoarr(any)(NULL);
		return (gen_cvt_array_tostr(array));
	}
	else return (strdup("(bad variant)"));
	array = c_settoarr(any)(set);
	result = gen_cvt_array_tostr(array);
	if (array != NULL)
		c_arrdel(any)(&array);
	c_setdel(any)(&set);
	return (result);
}
void	print_test_settoarr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_settoarr, variant)
	TEST_PRINT(str,	settoarr, "variant=%u", variant)
	TEST_FREE()
}
void	test_settoarr(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                | ARGS
	print_test_settoarr("settoarr (filled)      ",	FALSE,	"[Omae,  wa , mou ]",      0);
	print_test_settoarr("settoarr (empty set)   ",	FALSE,	"[]",                      1);
	print_test_settoarr("settoarr (null set)    ",	FALSE,	"(null)",                  2);
}
#endif



#ifndef c_lsttoset
void test_lsttoset(void)	{}
#warning "lsttoset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lsttoset(t_uint variant)
{
	s_list(any)*	list;
	s_set(any)*	set;
	char*	result;

	if (variant == 0) // convert a list without duplicates
		list = gen_cvt_list_fixture(3);
	else if (variant == 1) // convert a list with duplicates: they are removed
	{
		list = gen_cvt_list_fixture(2); // [Omae,  wa ]
		s_list(any)*	node = c_lstitem(any)(g_cvt_val[0]); // duplicate "Omae"
		node->next = list;
		list = node;
	}
	else if (variant == 2) // NULL list: error (NOTE: an empty list *is* `NULL`, so it cannot be converted)
	{
		set = c_lsttoset(any)(NULL);
		return (gen_cvt_set_tostr(set));
	}
	else return (strdup("(bad variant)"));
	set = c_lsttoset(any)(list);
	result = gen_cvt_set_tostr(set);
	if (set != NULL)
		c_setdel(any)(&set);
	c_lstdel(any)(&list);
	return (result);
}
void	print_test_lsttoset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lsttoset, variant)
	TEST_PRINT(str,	lsttoset, "variant=%u", variant)
	TEST_FREE()
}
void	test_lsttoset(void)
{
//	| TEST FUNCTION    | TEST NAME                  |TESTFLAG| EXPECTING            | ARGS
	print_test_lsttoset("lsttoset (no duplicates) ",	FALSE,	"{Omae,  wa , mou }",  0);
	print_test_lsttoset("lsttoset (deduplicates)  ",	FALSE,	"{Omae,  wa }",        1);
	print_test_lsttoset("lsttoset (null list)     ",	FALSE,	"(null)",              2);
}
#endif



#ifndef c_settolst
void test_settolst(void)	{}
#warning "settolst() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_settolst(t_uint variant)
{
	s_set(any)*	set;
	s_list(any)*	list;
	char*	result;

	if (variant == 0) // convert a filled set
		set = c_setcreate(any)(3, g_cvt_val[0], g_cvt_val[1], g_cvt_val[2]);
	else if (variant == 1) // convert an empty set: gives an empty (`NULL`) list, with no error
		set = c_setnew(any)();
	else if (variant == 2) // round-trip: set -> list -> set must be equal to the original
	{
		s_set(any)*	source = c_setcreate(any)(3, g_cvt_val[0], g_cvt_val[1], g_cvt_val[2]);
		s_set(any)*	back;
		list = c_settolst(any)(source);
		back = c_lsttoset(any)(list);
		result = strdup(c_setequ(any)(source, back) ? "(round-trip equals)" : "(round-trip differs)");
		c_setdel(any)(&back);
		if (list != NULL)
			c_lstdel(any)(&list);
		c_setdel(any)(&source);
		return (result);
	}
	else return (strdup("(bad variant)"));
	list = c_settolst(any)(set);
	result = gen_cvt_list_tostr(list);
	if (list != NULL)
		c_lstdel(any)(&list);
	c_setdel(any)(&set);
	return (result);
}
void	print_test_settolst(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_settolst, variant)
	TEST_PRINT(str,	settolst, "variant=%u", variant)
	TEST_FREE()
}
void	test_settolst(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                | ARGS
	print_test_settolst("settolst (filled)      ",	FALSE,	"[Omae,  wa , mou ]",      0);
	print_test_settolst("settolst (empty set)   ",	FALSE,	"[]",                      1);
	print_test_settolst("settolst (round-trip)  ",	FALSE,	"(round-trip equals)",     2);
}
#endif



/*============================================================================*\
||                              Dict Conversions                              ||
\*============================================================================*/

#ifndef c_dicttoarr
void test_dicttoarr(void)	{}
#warning "dicttoarr() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dicttoarr(t_uint variant)
{
	s_dict(any)*	dict;
	s_keyval(any)*	keyvals;
	char	buffer[256];
	t_uint	i;

	if (variant == 0) // convert a filled dict (serializing until the NULL-key terminator pair)
		dict = c_dictcreate(any)(3, "first", g_cvt_val[0], "second", g_cvt_val[1], "third", g_cvt_val[2]);
	else if (variant == 1) // convert an empty dict: only the terminator pair
		dict = c_dictnew(any)();
	else if (variant == 2) // NULL dict: error
	{
		keyvals = c_dicttoarr(any)(NULL);
		return (strdup(keyvals == NULL ? "(null)" : "(non-null)"));
	}
	else if (variant == 3) // the returned keys are independent copies (the dict can be freed)
	{
		dict = c_dictcreate(any)(2, "first", g_cvt_val[0], "second", g_cvt_val[1]);
		keyvals = c_dicttoarr(any)(dict);
		c_dictdel(any)(&dict); // free the dict before reading the keyvals
		buffer[0] = '\0';
		for (i = 0; keyvals[i].key != NULL; ++i)
		{
			strcat(buffer, "[");
			strcat(buffer, keyvals[i].key);
			strcat(buffer, "]");
			c_keyvalfree(any)(&keyvals[i]);
		}
		free(keyvals);
		return (strdup(buffer));
	}
	else return (strdup("(bad variant)"));
	keyvals = c_dicttoarr(any)(dict);
	if (keyvals == NULL)
	{
		c_dictdel(any)(&dict);
		return (strdup("(null)"));
	}
	buffer[0] = '\0';
	for (i = 0; keyvals[i].key != NULL; ++i)
	{
		strcat(buffer, "[");
		strcat(buffer, keyvals[i].key);
		strcat(buffer, ":");
		strcat(buffer, (char const*)keyvals[i].value);
		strcat(buffer, "]");
		c_keyvalfree(any)(&keyvals[i]);
	}
	free(keyvals);
	c_dictdel(any)(&dict);
	return (strdup(buffer));
}
void	print_test_dicttoarr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dicttoarr, variant)
	TEST_PRINT(str,	dicttoarr, "variant=%u", variant)
	TEST_FREE()
}
void	test_dicttoarr(void)
{
//	| TEST FUNCTION     | TEST NAME                    |TESTFLAG| EXPECTING                                   | ARGS
	print_test_dicttoarr("dicttoarr (filled)          ",	FALSE,	"[first:Omae][second: wa ][third:mou ]",      0);
	print_test_dicttoarr("dicttoarr (empty dict)      ",	FALSE,	"",                                           1);
	print_test_dicttoarr("dicttoarr (null dict)       ",	FALSE,	"(null)",                                     2);
	print_test_dicttoarr("dicttoarr (keys are copies) ",	FALSE,	"[first][second]",                            3);
}
#endif



#ifndef c_dicttokeys
void test_dicttokeys(void)	{}
#warning "dicttokeys() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dicttokeys(t_uint variant)
{
	s_dict(any)*	dict;
	t_char**	keys;
	char	buffer[256];
	t_uint	i;

	if (variant == 0) // convert a filled dict (keys in insertion order, NULL-terminated)
		dict = c_dictcreate(any)(3, "first", g_cvt_val[0], "second", g_cvt_val[1], "third", g_cvt_val[2]);
	else if (variant == 1) // convert an empty dict: only the NULL terminator
		dict = c_dictnew(any)();
	else if (variant == 2) // NULL dict: error
	{
		keys = c_dicttokeys(any)(NULL);
		return (strdup(keys == NULL ? "(null)" : "(non-null)"));
	}
	else return (strdup("(bad variant)"));
	keys = c_dicttokeys(any)(dict);
	c_dictdel(any)(&dict); // free the dict before reading the keys (they are independent copies)
	if (keys == NULL)
		return (strdup("(null)"));
	buffer[0] = '\0';
	strcat(buffer, "(");
	for (i = 0; keys[i] != NULL; ++i)
	{
		if (i > 0)
			strcat(buffer, ", ");
		strcat(buffer, keys[i]);
		free(keys[i]);
	}
	strcat(buffer, ")");
	free(keys);
	return (strdup(buffer));
}
void	print_test_dicttokeys(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dicttokeys, variant)
	TEST_PRINT(str,	dicttokeys, "variant=%u", variant)
	TEST_FREE()
}
void	test_dicttokeys(void)
{
//	| TEST FUNCTION      | TEST NAME                |TESTFLAG| EXPECTING                  | ARGS
	print_test_dicttokeys("dicttokeys (filled)     ",	FALSE,	"(first, second, third)",    0);
	print_test_dicttokeys("dicttokeys (empty dict) ",	FALSE,	"()",                        1);
	print_test_dicttokeys("dicttokeys (null dict)  ",	FALSE,	"(null)",                    2);
}
#endif



#ifndef c_dicttovals
void test_dicttovals(void)	{}
#warning "dicttovals() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dicttovals(t_uint variant)
{
	s_dict(any)*	dict;
	s_array(any)*	array;
	char*	result;

	if (variant == 0) // convert a filled dict (values in insertion order)
		dict = c_dictcreate(any)(3, "first", g_cvt_val[0], "second", g_cvt_val[1], "third", g_cvt_val[2]);
	else if (variant == 1) // convert an empty dict: gives an empty array
		dict = c_dictnew(any)();
	else if (variant == 2) // NULL dict: error
	{
		array = c_dicttovals(any)(NULL);
		return (gen_cvt_array_tostr(array));
	}
	else if (variant == 3) // duplicate values in the dict are all kept (unlike a set conversion)
		dict = c_dictcreate(any)(3, "first", g_cvt_val[0], "second", g_cvt_val[0], "third", g_cvt_val[0]);
	else return (strdup("(bad variant)"));
	array = c_dicttovals(any)(dict);
	result = gen_cvt_array_tostr(array);
	if (array != NULL)
		c_arrdel(any)(&array);
	c_dictdel(any)(&dict);
	return (result);
}
void	print_test_dicttovals(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dicttovals, variant)
	TEST_PRINT(str,	dicttovals, "variant=%u", variant)
	TEST_FREE()
}
void	test_dicttovals(void)
{
//	| TEST FUNCTION      | TEST NAME                    |TESTFLAG| EXPECTING                | ARGS
	print_test_dicttovals("dicttovals (filled)         ",	FALSE,	"[Omae,  wa , mou ]",      0);
	print_test_dicttovals("dicttovals (empty dict)     ",	FALSE,	"[]",                      1);
	print_test_dicttovals("dicttovals (null dict)      ",	FALSE,	"(null)",                  2);
	print_test_dicttovals("dicttovals (duplicate vals) ",	FALSE,	"[Omae, Omae, Omae]",      3);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_convert(void)
{
	print_suite_title("libccc/generic/convert");

	print_nonstd();

	test_arrtolst();
	test_lsttoarr();

	test_arrtoset();
	test_settoarr();
	test_lsttoset();
	test_settolst();

	test_dicttoarr();
	test_dicttokeys();
	test_dicttovals();

	return (OK);
}
